#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct MPContext {int osd_show_pos; int osd_msg_next_duration; int osd_force_update; int /*<<< orphan*/  osd_msg_visible; int /*<<< orphan*/  osd_msg_text; TYPE_1__* opts; } ;
struct TYPE_2__ {int osd_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_time_sec () ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_vasprintf (struct MPContext*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_osd_msg_va(struct MPContext *mpctx, int level, int time,
                           const char *fmt, va_list ap)
{
    if (level > mpctx->opts->osd_level)
        return false;

    talloc_free(mpctx->osd_msg_text);
    mpctx->osd_msg_text = talloc_vasprintf(mpctx, fmt, ap);
    mpctx->osd_show_pos = false;
    mpctx->osd_msg_next_duration = time / 1000.0;
    mpctx->osd_force_update = true;
    mp_wakeup_core(mpctx);
    if (mpctx->osd_msg_next_duration <= 0)
        mpctx->osd_msg_visible = mp_time_sec();
    return true;
}