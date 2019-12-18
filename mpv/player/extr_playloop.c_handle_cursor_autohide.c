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
struct vo {int dummy; } ;
struct MPOpts {double cursor_autohide_delay; TYPE_1__* vo; scalar_t__ cursor_autohide_fs; } ;
struct MPContext {int mouse_cursor_visible; unsigned int mouse_event_ts; double mouse_timer; int /*<<< orphan*/  input; struct vo* video_out; struct MPOpts* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  fullscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_SET_CURSOR_VISIBILITY ; 
 unsigned int mp_input_get_mouse_event_counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 double mp_time_sec () ; 
 int /*<<< orphan*/  vo_control (struct vo*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void handle_cursor_autohide(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    struct vo *vo = mpctx->video_out;

    if (!vo)
        return;

    bool mouse_cursor_visible = mpctx->mouse_cursor_visible;
    double now = mp_time_sec();

    unsigned mouse_event_ts = mp_input_get_mouse_event_counter(mpctx->input);
    if (mpctx->mouse_event_ts != mouse_event_ts) {
        mpctx->mouse_event_ts = mouse_event_ts;
        mpctx->mouse_timer = now + opts->cursor_autohide_delay / 1000.0;
        mouse_cursor_visible = true;
    }

    if (mpctx->mouse_timer > now) {
        mp_set_timeout(mpctx, mpctx->mouse_timer - now);
    } else {
        mouse_cursor_visible = false;
    }

    if (opts->cursor_autohide_delay == -1)
        mouse_cursor_visible = true;

    if (opts->cursor_autohide_delay == -2)
        mouse_cursor_visible = false;

    if (opts->cursor_autohide_fs && !opts->vo->fullscreen)
        mouse_cursor_visible = true;

    if (mouse_cursor_visible != mpctx->mouse_cursor_visible)
        vo_control(vo, VOCTRL_SET_CURSOR_VISIBILITY, &mouse_cursor_visible);
    mpctx->mouse_cursor_visible = mouse_cursor_visible;
}