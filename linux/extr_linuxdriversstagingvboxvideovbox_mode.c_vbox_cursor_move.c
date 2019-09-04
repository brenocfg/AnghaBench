#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vbox_private {scalar_t__ cursor_data_size; scalar_t__ cursor_hot_x; scalar_t__ cursor_hot_y; int /*<<< orphan*/  cursor_data; int /*<<< orphan*/  cursor_height; int /*<<< orphan*/  cursor_width; int /*<<< orphan*/  guest_pool; scalar_t__ single_framebuffer; } ;
struct drm_crtc {scalar_t__ x; scalar_t__ y; TYPE_1__* dev; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {scalar_t__ x_hint; scalar_t__ y_hint; } ;
struct TYPE_3__ {struct vbox_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ VBOX_MOUSE_POINTER_ALPHA ; 
 scalar_t__ VBOX_MOUSE_POINTER_SHAPE ; 
 scalar_t__ VBOX_MOUSE_POINTER_VISIBLE ; 
 int hgsmi_cursor_position (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int hgsmi_update_pointer_shape (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_vbox_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int vbox_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct vbox_private *vbox = crtc->dev->dev_private;
	u32 flags = VBOX_MOUSE_POINTER_VISIBLE |
	    VBOX_MOUSE_POINTER_SHAPE | VBOX_MOUSE_POINTER_ALPHA;
	s32 crtc_x =
	    vbox->single_framebuffer ? crtc->x : to_vbox_crtc(crtc)->x_hint;
	s32 crtc_y =
	    vbox->single_framebuffer ? crtc->y : to_vbox_crtc(crtc)->y_hint;
	u32 host_x, host_y;
	u32 hot_x = 0;
	u32 hot_y = 0;
	int ret;

	/*
	 * We compare these to unsigned later and don't
	 * need to handle negative.
	 */
	if (x + crtc_x < 0 || y + crtc_y < 0 || vbox->cursor_data_size == 0)
		return 0;

	ret = hgsmi_cursor_position(vbox->guest_pool, true, x + crtc_x,
				    y + crtc_y, &host_x, &host_y);

	/*
	 * The only reason we have vbox_cursor_move() is that some older clients
	 * might use DRM_IOCTL_MODE_CURSOR instead of DRM_IOCTL_MODE_CURSOR2 and
	 * use DRM_MODE_CURSOR_MOVE to set the hot-spot.
	 *
	 * However VirtualBox 5.0.20 and earlier has a bug causing it to return
	 * 0,0 as host cursor location after a save and restore.
	 *
	 * To work around this we ignore a 0, 0 return, since missing the odd
	 * time when it legitimately happens is not going to hurt much.
	 */
	if (ret || (host_x == 0 && host_y == 0))
		return ret;

	if (x + crtc_x < host_x)
		hot_x = min(host_x - x - crtc_x, vbox->cursor_width);
	if (y + crtc_y < host_y)
		hot_y = min(host_y - y - crtc_y, vbox->cursor_height);

	if (hot_x == vbox->cursor_hot_x && hot_y == vbox->cursor_hot_y)
		return 0;

	vbox->cursor_hot_x = hot_x;
	vbox->cursor_hot_y = hot_y;

	return hgsmi_update_pointer_shape(vbox->guest_pool, flags,
			hot_x, hot_y, vbox->cursor_width, vbox->cursor_height,
			vbox->cursor_data, vbox->cursor_data_size);
}