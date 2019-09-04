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
struct vo_wayland_state {int allocated_cursor_scale; int scaling; int /*<<< orphan*/  default_cursor; scalar_t__ cursor_theme; int /*<<< orphan*/  shm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo_wayland_state*,char*) ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_cursor_theme_get_cursor (scalar_t__,char*) ; 
 scalar_t__ wl_cursor_theme_load (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spawn_cursor(struct vo_wayland_state *wl)
{
    if (wl->allocated_cursor_scale == wl->scaling) /* Reuse if size is identical */
        return 0;
    else if (wl->cursor_theme)
        wl_cursor_theme_destroy(wl->cursor_theme);

    wl->cursor_theme = wl_cursor_theme_load(NULL, 32*wl->scaling, wl->shm);
    if (!wl->cursor_theme) {
        MP_ERR(wl, "Unable to load cursor theme!\n");
        return 1;
    }

    wl->default_cursor = wl_cursor_theme_get_cursor(wl->cursor_theme, "left_ptr");
    if (!wl->default_cursor) {
        MP_ERR(wl, "Unable to load cursor theme!\n");
        return 1;
    }

    wl->allocated_cursor_scale = wl->scaling;

    return 0;
}