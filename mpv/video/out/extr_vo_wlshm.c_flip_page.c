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
struct vo_wayland_state {int /*<<< orphan*/  surface; int /*<<< orphan*/  geometry; } ;
struct vo {struct vo_wayland_state* wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_rect_h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_rect_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_damage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct vo_wayland_state *wl = vo->wl;

    wl_surface_damage(wl->surface, 0, 0, mp_rect_w(wl->geometry),
                      mp_rect_h(wl->geometry));
    wl_surface_commit(wl->surface);
}