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
struct MPOpts {double* ab_loop; } ;
struct TYPE_2__ {int type; scalar_t__ num_stops; int /*<<< orphan*/  stops; } ;
struct MPContext {TYPE_1__ osd_progbar; int /*<<< orphan*/  osd; struct MPOpts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct MPContext*,int /*<<< orphan*/ ,scalar_t__,float) ; 
 double chapter_start_time (struct MPContext*,int) ; 
 double get_ab_loop_start_time (struct MPContext*) ; 
 int get_chapter_count (struct MPContext*) ; 
 double get_time_length (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  osd_set_progbar (int /*<<< orphan*/ ,TYPE_1__*) ; 

void set_osd_bar_chapters(struct MPContext *mpctx, int type)
{
    struct MPOpts *opts = mpctx->opts;
    if (mpctx->osd_progbar.type != type)
        return;

    mpctx->osd_progbar.num_stops = 0;
    double len = get_time_length(mpctx);
    if (len > 0) {
        double ab_loop_start_time = get_ab_loop_start_time(mpctx);
        if (opts->ab_loop[0] != MP_NOPTS_VALUE ||
            (ab_loop_start_time != MP_NOPTS_VALUE &&
               opts->ab_loop[1] != MP_NOPTS_VALUE))
        {
            MP_TARRAY_APPEND(mpctx, mpctx->osd_progbar.stops,
                        mpctx->osd_progbar.num_stops, ab_loop_start_time / len);
        }
        if (opts->ab_loop[1] != MP_NOPTS_VALUE) {
            MP_TARRAY_APPEND(mpctx, mpctx->osd_progbar.stops,
                        mpctx->osd_progbar.num_stops, opts->ab_loop[1] / len);
        }
        if (mpctx->osd_progbar.num_stops == 0) {
            int num = get_chapter_count(mpctx);
            for (int n = 0; n < num; n++) {
                double time = chapter_start_time(mpctx, n);
                if (time >= 0) {
                    float pos = time / len;
                    MP_TARRAY_APPEND(mpctx, mpctx->osd_progbar.stops,
                                     mpctx->osd_progbar.num_stops, pos);
                }
            }
        }
    }
    osd_set_progbar(mpctx->osd, &mpctx->osd_progbar);
    mp_wakeup_core(mpctx);
}