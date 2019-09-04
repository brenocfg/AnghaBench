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
struct vo_wayland_state {int /*<<< orphan*/  xdg_toplevel; } ;

/* Variables and functions */
 int VO_NOTAVAIL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  xdg_toplevel_set_title (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int update_window_title(struct vo_wayland_state *wl, char *title)
{
    if (!wl->xdg_toplevel)
        return VO_NOTAVAIL;
    xdg_toplevel_set_title(wl->xdg_toplevel, title);
    return VO_TRUE;
}