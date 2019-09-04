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
struct vo_wayland_state {int /*<<< orphan*/  xdg_toplevel; int /*<<< orphan*/  xdg_surface; int /*<<< orphan*/  surface; int /*<<< orphan*/  wm_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdg_surface_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vo_wayland_state*) ; 
 int /*<<< orphan*/  xdg_surface_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_surface_listener ; 
 int /*<<< orphan*/  xdg_toplevel_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vo_wayland_state*) ; 
 int /*<<< orphan*/  xdg_toplevel_listener ; 
 int /*<<< orphan*/  xdg_toplevel_set_app_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdg_toplevel_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdg_wm_base_get_xdg_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_xdg_surface(struct vo_wayland_state *wl)
{
    wl->xdg_surface = xdg_wm_base_get_xdg_surface(wl->wm_base, wl->surface);
    xdg_surface_add_listener(wl->xdg_surface, &xdg_surface_listener, wl);

    wl->xdg_toplevel = xdg_surface_get_toplevel(wl->xdg_surface);
    xdg_toplevel_add_listener(wl->xdg_toplevel, &xdg_toplevel_listener, wl);

    xdg_toplevel_set_title (wl->xdg_toplevel, "mpv");
    xdg_toplevel_set_app_id(wl->xdg_toplevel, "mpv");

    return 0;
}