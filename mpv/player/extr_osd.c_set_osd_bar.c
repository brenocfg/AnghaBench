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
struct MPOpts {int osd_level; double osd_duration; int /*<<< orphan*/  osd_bar_visible; int /*<<< orphan*/  video_osd; } ;
struct TYPE_2__ {int type; double value; scalar_t__ num_stops; int /*<<< orphan*/  stops; } ;
struct MPContext {TYPE_1__ osd_progbar; int /*<<< orphan*/  osd; scalar_t__ osd_visible; struct MPOpts* opts; scalar_t__ video_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct MPContext*,int /*<<< orphan*/ ,scalar_t__,float) ; 
 scalar_t__ mp_time_sec () ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  osd_set_progbar (int /*<<< orphan*/ ,TYPE_1__*) ; 

void set_osd_bar(struct MPContext *mpctx, int type,
                 double min, double max, double neutral, double val)
{
    struct MPOpts *opts = mpctx->opts;
    bool video_osd = mpctx->video_out && mpctx->opts->video_osd;
    if (opts->osd_level < 1 || !opts->osd_bar_visible || !video_osd)
        return;

    mpctx->osd_visible = mp_time_sec() + opts->osd_duration / 1000.0;
    mpctx->osd_progbar.type = type;
    mpctx->osd_progbar.value = (val - min) / (max - min);
    mpctx->osd_progbar.num_stops = 0;
    if (neutral > min && neutral < max) {
        float pos = (neutral - min) / (max - min);
        MP_TARRAY_APPEND(mpctx, mpctx->osd_progbar.stops,
                         mpctx->osd_progbar.num_stops, pos);
    }
    osd_set_progbar(mpctx->osd, &mpctx->osd_progbar);
    mp_wakeup_core(mpctx);
}