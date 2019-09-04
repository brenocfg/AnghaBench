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
typedef  int /*<<< orphan*/  uint32_t ;
struct vo_wayland_state {int /*<<< orphan*/  seat; scalar_t__ xdg_toplevel; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdg_toplevel_move (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void window_move(struct vo_wayland_state *wl, uint32_t serial)
{
    if (wl->xdg_toplevel)
        xdg_toplevel_move(wl->xdg_toplevel, wl->seat, serial);
}