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
struct vo_wayland_state {int allocated_cursor_scale; int scaling; int /*<<< orphan*/  default_cursor; int /*<<< orphan*/  cursor_theme; int /*<<< orphan*/  shm; } ;

/* Variables and functions */
 long INT_MAX ; 
 int /*<<< orphan*/  MP_ERR (struct vo_wayland_state*,char*) ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 long strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_cursor_theme_get_cursor (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_cursor_theme_load (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spawn_cursor(struct vo_wayland_state *wl)
{
    if (wl->allocated_cursor_scale == wl->scaling) /* Reuse if size is identical */
        return 0;
    else if (wl->cursor_theme)
        wl_cursor_theme_destroy(wl->cursor_theme);

    const char *size_str = getenv("XCURSOR_SIZE");
    int size = 32;
    if (size_str != NULL) {
        errno = 0;
        char *end;
        long size_long = strtol(size_str, &end, 10);
        if (!*end && !errno && size_long > 0 && size_long <= INT_MAX)
            size = (int)size_long;
    }

    wl->cursor_theme = wl_cursor_theme_load(NULL, size*wl->scaling, wl->shm);
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