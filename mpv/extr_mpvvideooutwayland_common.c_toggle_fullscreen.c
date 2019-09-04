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
struct vo_wayland_state {int /*<<< orphan*/  xdg_toplevel; scalar_t__ fullscreen; } ;

/* Variables and functions */
 int VO_NOTAVAIL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  xdg_toplevel_set_fullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_toplevel_unset_fullscreen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int toggle_fullscreen(struct vo_wayland_state *wl)
{
    if (!wl->xdg_toplevel)
        return VO_NOTAVAIL;
    if (wl->fullscreen)
        xdg_toplevel_unset_fullscreen(wl->xdg_toplevel);
    else
        xdg_toplevel_set_fullscreen(wl->xdg_toplevel, NULL);
    return VO_TRUE;
}