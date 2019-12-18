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
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;
struct vo_wayland_state {int /*<<< orphan*/ * xkb_keymap; int /*<<< orphan*/  xkb_state; int /*<<< orphan*/  xkb_context; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MP_ERR (struct vo_wayland_state*,char*) ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1 ; 
 int /*<<< orphan*/  XKB_KEYMAP_FORMAT_TEXT_V1 ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 char* mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,scalar_t__) ; 
 int /*<<< orphan*/ * xkb_keymap_new_from_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_keymap_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkb_state_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyboard_handle_keymap(void *data, struct wl_keyboard *wl_keyboard,
                                   uint32_t format, int32_t fd, uint32_t size)
{
    struct vo_wayland_state *wl = data;
    char *map_str;

    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        return;
    }

    map_str = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (map_str == MAP_FAILED) {
        close(fd);
        return;
    }

    wl->xkb_keymap = xkb_keymap_new_from_string(wl->xkb_context, map_str,
                                                XKB_KEYMAP_FORMAT_TEXT_V1, 0);

    munmap(map_str, size);
    close(fd);

    if (!wl->xkb_keymap) {
        MP_ERR(wl, "failed to compile keymap\n");
        return;
    }

    wl->xkb_state = xkb_state_new(wl->xkb_keymap);
    if (!wl->xkb_state) {
        MP_ERR(wl, "failed to create XKB state\n");
        xkb_keymap_unref(wl->xkb_keymap);
        wl->xkb_keymap = NULL;
        return;
    }
}