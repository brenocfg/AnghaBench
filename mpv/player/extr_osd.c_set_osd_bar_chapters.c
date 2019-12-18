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
struct TYPE_2__ {int type; scalar_t__ num_stops; int /*<<< orphan*/  stops; } ;
struct MPContext {TYPE_1__ osd_progbar; int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct MPContext*,int /*<<< orphan*/ ,scalar_t__,float) ; 
 double chapter_start_time (struct MPContext*,int) ; 
 int get_ab_loop_times (struct MPContext*,double*) ; 
 int get_chapter_count (struct MPContext*) ; 
 double get_time_length (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  osd_set_progbar (int /*<<< orphan*/ ,TYPE_1__*) ; 

void set_osd_bar_chapters(struct MPContext *mpctx, int type)
{
    if (mpctx->osd_progbar.type != type)
        return;

    mpctx->osd_progbar.num_stops = 0;
    double len = get_time_length(mpctx);
    if (len > 0) {
        // Always render the loop points, even if they're incomplete.
        double ab[2];
        bool valid = get_ab_loop_times(mpctx, ab);
        for (int n = 0; n < 2; n++) {
            if (ab[n] != MP_NOPTS_VALUE) {
                MP_TARRAY_APPEND(mpctx, mpctx->osd_progbar.stops,
                                 mpctx->osd_progbar.num_stops, ab[n] / len);
            }
        }
        if (!valid) {
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