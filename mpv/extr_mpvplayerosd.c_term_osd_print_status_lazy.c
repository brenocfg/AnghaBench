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
struct MPOpts {scalar_t__ term_osd_bar; scalar_t__ quiet; int /*<<< orphan*/  use_terminal; } ;
struct MPContext {int /*<<< orphan*/  log; scalar_t__ stop_play; int /*<<< orphan*/  playing; int /*<<< orphan*/  playing_msg_shown; int /*<<< orphan*/  playback_initialized; struct MPOpts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_term_osd_bar (struct MPContext*,char**,int) ; 
 char* get_term_status_msg (struct MPContext*) ; 
 int /*<<< orphan*/  mp_msg_flush_status_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saddf (char**,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  term_osd_set_status_lazy (struct MPContext*,char*) ; 
 int /*<<< orphan*/  terminal_get_size (int*,int*) ; 
 int /*<<< orphan*/  update_vo_playback_state (struct MPContext*) ; 
 int /*<<< orphan*/  update_window_title (struct MPContext*,int) ; 

__attribute__((used)) static void term_osd_print_status_lazy(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;

    update_window_title(mpctx, false);
    update_vo_playback_state(mpctx);

    if (!opts->use_terminal)
        return;

    if (opts->quiet || !mpctx->playback_initialized ||
        !mpctx->playing_msg_shown || mpctx->stop_play)
    {
        if (!mpctx->playing || mpctx->stop_play) {
            mp_msg_flush_status_line(mpctx->log);
            term_osd_set_status_lazy(mpctx, "");
        }
        return;
    }

    char *line = get_term_status_msg(mpctx);

    if (opts->term_osd_bar) {
        saddf(&line, "\n");
        int w = 80, h = 24;
        terminal_get_size(&w, &h);
        add_term_osd_bar(mpctx, &line, w);
    }

    term_osd_set_status_lazy(mpctx, line);
    talloc_free(line);
}