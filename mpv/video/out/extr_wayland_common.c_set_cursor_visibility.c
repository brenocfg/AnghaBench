#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl_cursor_image {int hotspot_x; int hotspot_y; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct wl_buffer {int dummy; } ;
struct vo_wayland_state {int cursor_visible; int scaling; int /*<<< orphan*/  pointer_id; int /*<<< orphan*/  pointer; int /*<<< orphan*/ * cursor_surface; TYPE_1__* default_cursor; } ;
struct TYPE_2__ {struct wl_cursor_image** images; } ;

/* Variables and functions */
 int VO_FALSE ; 
 int VO_NOTAVAIL ; 
 int VO_TRUE ; 
 scalar_t__ spawn_cursor (struct vo_wayland_state*) ; 
 struct wl_buffer* wl_cursor_image_get_buffer (struct wl_cursor_image*) ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wl_surface_attach (int /*<<< orphan*/ *,struct wl_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_surface_damage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int set_cursor_visibility(struct vo_wayland_state *wl, bool on)
{
    if (!wl->pointer)
        return VO_NOTAVAIL;
    wl->cursor_visible = on;
    if (on) {
        if (spawn_cursor(wl))
            return VO_FALSE;
        struct wl_cursor_image *img = wl->default_cursor->images[0];
        struct wl_buffer *buffer = wl_cursor_image_get_buffer(img);
        if (!buffer)
            return VO_FALSE;
        wl_pointer_set_cursor(wl->pointer, wl->pointer_id, wl->cursor_surface,
                              img->hotspot_x/wl->scaling, img->hotspot_y/wl->scaling);
        wl_surface_set_buffer_scale(wl->cursor_surface, wl->scaling);
        wl_surface_attach(wl->cursor_surface, buffer, 0, 0);
        wl_surface_damage(wl->cursor_surface, 0, 0, img->width, img->height);
        wl_surface_commit(wl->cursor_surface);
    } else {
        wl_pointer_set_cursor(wl->pointer, wl->pointer_id, NULL, 0, 0);
    }
    return VO_TRUE;
}