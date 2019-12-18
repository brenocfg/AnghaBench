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
struct vo_x11_state {int wm_type; long orig_layer; int /*<<< orphan*/  window; scalar_t__ parent; } ;
struct vo {struct vo_x11_state* x11; } ;

/* Variables and functions */
 long CurrentTime ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*,long,...) ; 
 long WIN_LAYER_ABOVE_DOCK ; 
 long WIN_LAYER_NORMAL ; 
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  _WIN_LAYER ; 
 int vo_wm_ABOVE ; 
 int vo_wm_LAYER ; 
 int vo_wm_STAYS_ON_TOP ; 
 int /*<<< orphan*/  x11_get_property_copy (struct vo_x11_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long*,int) ; 
 int /*<<< orphan*/  x11_send_ewmh_msg (struct vo_x11_state*,char*,long*) ; 
 int /*<<< orphan*/  x11_set_ewmh_state (struct vo_x11_state*,char*,int) ; 

__attribute__((used)) static void vo_x11_setlayer(struct vo *vo, bool ontop)
{
    struct vo_x11_state *x11 = vo->x11;
    if (x11->parent || !x11->window)
        return;

    if (x11->wm_type & (vo_wm_STAYS_ON_TOP | vo_wm_ABOVE)) {
        char *state = "_NET_WM_STATE_ABOVE";

        // Not in EWMH - but the old code preferred this (maybe it is "better")
        if (x11->wm_type & vo_wm_STAYS_ON_TOP)
            state = "_NET_WM_STATE_STAYS_ON_TOP";

        x11_set_ewmh_state(x11, state, ontop);

        MP_VERBOSE(x11, "NET style stay on top (%d). Using state %s.\n",
                   ontop, state);
    } else if (x11->wm_type & vo_wm_LAYER) {
        if (!x11->orig_layer) {
            x11->orig_layer = WIN_LAYER_NORMAL;
            x11_get_property_copy(x11, x11->window, XA(x11, _WIN_LAYER),
                                  XA_CARDINAL, 32, &x11->orig_layer, sizeof(long));
            MP_VERBOSE(x11, "original window layer is %ld.\n", x11->orig_layer);
        }

        long params[5] = {0};
        // if not fullscreen, stay on default layer
        params[0] = ontop ? WIN_LAYER_ABOVE_DOCK : x11->orig_layer;
        params[1] = CurrentTime;
        MP_VERBOSE(x11, "Layered style stay on top (layer %ld).\n", params[0]);
        x11_send_ewmh_msg(x11, "_WIN_LAYER", params);
    }
}