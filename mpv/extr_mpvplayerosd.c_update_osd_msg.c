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
struct osd_state {int dummy; } ;
struct MPOpts {int osd_level; int /*<<< orphan*/  video_osd; } ;
struct TYPE_2__ {int type; } ;
struct MPContext {int osd_force_update; int osd_idle_update; double osd_last_update; double osd_visible; double osd_function_visible; scalar_t__ osd_msg_next_duration; scalar_t__ osd_msg_visible; char* osd_msg_text; int osd_show_pos; TYPE_1__ osd_progbar; scalar_t__ osd_function; struct osd_state* osd; struct MPOpts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPCLAMP (double,int /*<<< orphan*/ ,int) ; 
 int OSD_BAR_SEEK ; 
 int /*<<< orphan*/  add_seek_osd_messages (struct MPContext*) ; 
 double get_current_pos_ratio (struct MPContext*,int) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 double mp_time_sec () ; 
 int /*<<< orphan*/  osd_set_progbar (struct osd_state*,TYPE_1__*) ; 
 int /*<<< orphan*/  osd_set_text (struct osd_state*,char*) ; 
 int /*<<< orphan*/  sadd_osd_status (char**,struct MPContext*,int) ; 
 char* talloc_asprintf_append (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  term_osd_print_status_lazy (struct MPContext*) ; 
 int /*<<< orphan*/  term_osd_set_text_lazy (struct MPContext*,char*) ; 
 int /*<<< orphan*/  term_osd_update (struct MPContext*) ; 
 int /*<<< orphan*/  update_osd_bar (struct MPContext*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void update_osd_msg(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    struct osd_state *osd = mpctx->osd;

    double now = mp_time_sec();

    if (!mpctx->osd_force_update) {
        // Assume nothing is going on at all.
        if (!mpctx->osd_idle_update)
            return;

        double delay = 0.050; // update the OSD at most this often
        double diff = now - mpctx->osd_last_update;
        if (diff < delay) {
            mp_set_timeout(mpctx, delay - diff);
            return;
        }
    }
    mpctx->osd_force_update = false;
    mpctx->osd_idle_update = false;
    mpctx->osd_last_update = now;

    if (mpctx->osd_visible) {
        double sleep = mpctx->osd_visible - now;
        if (sleep > 0) {
            mp_set_timeout(mpctx, sleep);
            mpctx->osd_idle_update = true;
        } else {
            mpctx->osd_visible = 0;
            mpctx->osd_progbar.type = -1; // disable
            osd_set_progbar(mpctx->osd, &mpctx->osd_progbar);
        }
    }

    if (mpctx->osd_function_visible) {
        double sleep = mpctx->osd_function_visible - now;
        if (sleep > 0) {
            mp_set_timeout(mpctx, sleep);
            mpctx->osd_idle_update = true;
        } else {
            mpctx->osd_function_visible = 0;
            mpctx->osd_function = 0;
        }
    }

    if (mpctx->osd_msg_next_duration > 0) {
        // This is done to avoid cutting the OSD message short if slow commands
        // are executed between setting the OSD message and showing it.
        mpctx->osd_msg_visible = now + mpctx->osd_msg_next_duration;
        mpctx->osd_msg_next_duration = 0;
    }

    if (mpctx->osd_msg_visible) {
        double sleep = mpctx->osd_msg_visible - now;
        if (sleep > 0) {
            mp_set_timeout(mpctx, sleep);
            mpctx->osd_idle_update = true;
        } else {
            talloc_free(mpctx->osd_msg_text);
            mpctx->osd_msg_text = NULL;
            mpctx->osd_msg_visible = 0;
            mpctx->osd_show_pos = false;
        }
    }

    add_seek_osd_messages(mpctx);

    if (mpctx->osd_progbar.type == OSD_BAR_SEEK) {
        double pos = get_current_pos_ratio(mpctx, false);
        update_osd_bar(mpctx, OSD_BAR_SEEK, 0, 1, MPCLAMP(pos, 0, 1));
    }

    term_osd_set_text_lazy(mpctx, mpctx->osd_msg_text);
    term_osd_print_status_lazy(mpctx);
    term_osd_update(mpctx);

    if (!opts->video_osd)
        return;

    int osd_level = opts->osd_level;
    if (mpctx->osd_show_pos)
        osd_level = 3;

    char *text = NULL;
    sadd_osd_status(&text, mpctx, osd_level);
    if (mpctx->osd_msg_text && mpctx->osd_msg_text[0]) {
        text = talloc_asprintf_append(text, "%s%s", text ? "\n" : "",
                                      mpctx->osd_msg_text);
    }
    osd_set_text(osd, text);
    talloc_free(text);
}