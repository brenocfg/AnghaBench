#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ao_chain {int /*<<< orphan*/  filter; } ;
struct MPContext {scalar_t__ audio_status; struct ao_chain* ao_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPSEEK_EXACT ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  issue_refresh_seek (struct MPContext*,int /*<<< orphan*/ ) ; 
 double mp_output_get_measured_total_delay (int /*<<< orphan*/ ) ; 
 scalar_t__ recreate_audio_filters (struct MPContext*) ; 

int reinit_audio_filters(struct MPContext *mpctx)
{
    struct ao_chain *ao_c = mpctx->ao_chain;
    if (!ao_c)
        return 0;

    double delay = mp_output_get_measured_total_delay(ao_c->filter);

    if (recreate_audio_filters(mpctx) < 0)
        return -1;

    double ndelay = mp_output_get_measured_total_delay(ao_c->filter);

    // Only force refresh if the amount of dropped buffered data is going to
    // cause "issues" for the A/V sync logic.
    if (mpctx->audio_status == STATUS_PLAYING && delay - ndelay >= 0.2)
        issue_refresh_seek(mpctx, MPSEEK_EXACT);
    return 1;
}