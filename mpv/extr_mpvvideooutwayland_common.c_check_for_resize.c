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
typedef  int /*<<< orphan*/  wl_fixed_t ;
struct vo_wayland_state {int /*<<< orphan*/  geometry; scalar_t__ maximized; scalar_t__ fullscreen; scalar_t__ touch_entries; } ;
typedef  enum xdg_toplevel_resize_edge { ____Placeholder_xdg_toplevel_resize_edge } xdg_toplevel_resize_edge ;

/* Variables and functions */
 int XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_LEFT ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_RIGHT ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_TOP ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT ; 
 int XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT ; 
 int const mp_rect_h (int /*<<< orphan*/ ) ; 
 int const mp_rect_w (int /*<<< orphan*/ ) ; 
 int wl_fixed_to_double (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_for_resize(struct vo_wayland_state *wl, wl_fixed_t x_w, wl_fixed_t y_w,
                            enum xdg_toplevel_resize_edge *edge)
{
    if (wl->touch_entries || wl->fullscreen || wl->maximized)
        return 0;

    const int edge_pixels = 64;
    int pos[2] = { wl_fixed_to_double(x_w), wl_fixed_to_double(y_w) };
    int left_edge   = pos[0] < edge_pixels;
    int top_edge    = pos[1] < edge_pixels;
    int right_edge  = pos[0] > (mp_rect_w(wl->geometry) - edge_pixels);
    int bottom_edge = pos[1] > (mp_rect_h(wl->geometry) - edge_pixels);

    if (left_edge) {
        *edge = XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
        if (top_edge)
            *edge = XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT;
        else if (bottom_edge)
            *edge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
    } else if (right_edge) {
        *edge = XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
        if (top_edge)
            *edge = XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT;
        else if (bottom_edge)
            *edge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
    } else if (top_edge) {
        *edge = XDG_TOPLEVEL_RESIZE_EDGE_TOP;
    } else if (bottom_edge) {
        *edge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
    } else {
        *edge = 0;
        return 0;
    }

    return 1;
}