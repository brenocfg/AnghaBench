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
struct mp_rect {scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
struct vo_x11_state {scalar_t__ fs; int wm_type; int pos_changed_during_fs; int size_changed_during_fs; int /*<<< orphan*/  display; int /*<<< orphan*/  window; struct mp_rect screenrc; struct mp_rect nofsrc; struct mp_rect winrc; scalar_t__ parent; } ;
struct vo {struct vo_x11_state* x11; struct mp_vo_opts* opts; } ;
struct mp_vo_opts {scalar_t__ fullscreen; scalar_t__ ontop; scalar_t__ border; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*) ; 
 int /*<<< orphan*/  RC_H (struct mp_rect) ; 
 int /*<<< orphan*/  RC_W (struct mp_rect) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMoveResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRaiseWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vo_wm_FULLSCREEN ; 
 int /*<<< orphan*/  vo_x11_decoration (struct vo*,int) ; 
 int /*<<< orphan*/  vo_x11_move_resize (struct vo*,int,int,struct mp_rect) ; 
 int /*<<< orphan*/  vo_x11_setlayer (struct vo*,int) ; 
 int /*<<< orphan*/  vo_x11_sizehint (struct vo*,struct mp_rect,int) ; 
 int /*<<< orphan*/  vo_x11_update_composition_hint (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_update_geometry (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_update_screeninfo (struct vo*) ; 
 int /*<<< orphan*/  x11_set_ewmh_state (struct vo_x11_state*,char*,scalar_t__) ; 

__attribute__((used)) static void vo_x11_fullscreen(struct vo *vo)
{
    struct mp_vo_opts *opts = vo->opts;
    struct vo_x11_state *x11 = vo->x11;

    if (opts->fullscreen == x11->fs)
        return;
    x11->fs = opts->fullscreen; // x11->fs now contains the new state
    if (x11->parent || !x11->window)
        return;

    // Save old state before entering fullscreen
    if (x11->fs) {
        vo_x11_update_geometry(vo);
        x11->nofsrc = x11->winrc;
    }

    struct mp_rect rc = x11->nofsrc;

    if (x11->wm_type & vo_wm_FULLSCREEN) {
        x11_set_ewmh_state(x11, "_NET_WM_STATE_FULLSCREEN", x11->fs);
        if (!x11->fs && (x11->pos_changed_during_fs ||
                         x11->size_changed_during_fs))
        {
            if (x11->screenrc.x0 == rc.x0 && x11->screenrc.x1 == rc.x1 &&
                x11->screenrc.y0 == rc.y0 && x11->screenrc.y1 == rc.y1)
            {
                // Workaround for some WMs switching back to FS in this case.
                MP_VERBOSE(x11, "avoiding triggering old-style fullscreen\n");
                rc.x1 -= 1;
                rc.y1 -= 1;
            }
            vo_x11_move_resize(vo, x11->pos_changed_during_fs,
                                   x11->size_changed_during_fs, rc);
        }
    } else {
        if (x11->fs) {
            vo_x11_update_screeninfo(vo);
            rc = x11->screenrc;
        }

        vo_x11_decoration(vo, opts->border && !x11->fs);
        vo_x11_sizehint(vo, rc, true);

        XMoveResizeWindow(x11->display, x11->window, rc.x0, rc.y0,
                          RC_W(rc), RC_H(rc));

        vo_x11_setlayer(vo, x11->fs || opts->ontop);

        XRaiseWindow(x11->display, x11->window);
        XFlush(x11->display);
    }

    x11->size_changed_during_fs = false;
    x11->pos_changed_during_fs = false;

    vo_x11_update_composition_hint(vo);
}