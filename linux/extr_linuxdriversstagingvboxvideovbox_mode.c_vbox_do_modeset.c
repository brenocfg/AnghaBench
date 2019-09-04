#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct vbox_private {int /*<<< orphan*/  guest_pool; scalar_t__ single_framebuffer; } ;
struct vbox_crtc {int x_hint; int y_hint; scalar_t__ crtc_id; int fb_offset; scalar_t__ blanked; scalar_t__ disconnected; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
struct drm_crtc {int x; int y; scalar_t__ enabled; TYPE_1__* dev; } ;
typedef  int s32 ;
struct TYPE_6__ {int* pitches; TYPE_2__* format; } ;
struct TYPE_5__ {int* cpp; } ;
struct TYPE_4__ {struct vbox_private* dev_private; } ;

/* Variables and functions */
 TYPE_3__* CRTC_FB (struct drm_crtc*) ; 
 int VBE_DISPI_ENABLED ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_BPP ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_ENABLE ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_VIRT_WIDTH ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_XRES ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_X_OFFSET ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_YRES ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_Y_OFFSET ; 
 int /*<<< orphan*/  VBVA_SCREEN_F_ACTIVE ; 
 int /*<<< orphan*/  VBVA_SCREEN_F_BLANK ; 
 int /*<<< orphan*/  VBVA_SCREEN_F_DISABLED ; 
 int /*<<< orphan*/  hgsmi_process_display_info (int /*<<< orphan*/ ,scalar_t__,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 struct vbox_crtc* to_vbox_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vbox_write_ioport (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vbox_do_modeset(struct drm_crtc *crtc,
			    const struct drm_display_mode *mode)
{
	struct vbox_crtc *vbox_crtc = to_vbox_crtc(crtc);
	struct vbox_private *vbox;
	int width, height, bpp, pitch;
	u16 flags;
	s32 x_offset, y_offset;

	vbox = crtc->dev->dev_private;
	width = mode->hdisplay ? mode->hdisplay : 640;
	height = mode->vdisplay ? mode->vdisplay : 480;
	bpp = crtc->enabled ? CRTC_FB(crtc)->format->cpp[0] * 8 : 32;
	pitch = crtc->enabled ? CRTC_FB(crtc)->pitches[0] : width * bpp / 8;
	x_offset = vbox->single_framebuffer ? crtc->x : vbox_crtc->x_hint;
	y_offset = vbox->single_framebuffer ? crtc->y : vbox_crtc->y_hint;

	/*
	 * This is the old way of setting graphics modes.  It assumed one screen
	 * and a frame-buffer at the start of video RAM.  On older versions of
	 * VirtualBox, certain parts of the code still assume that the first
	 * screen is programmed this way, so try to fake it.
	 */
	if (vbox_crtc->crtc_id == 0 && crtc->enabled &&
	    vbox_crtc->fb_offset / pitch < 0xffff - crtc->y &&
	    vbox_crtc->fb_offset % (bpp / 8) == 0) {
		vbox_write_ioport(VBE_DISPI_INDEX_XRES, width);
		vbox_write_ioport(VBE_DISPI_INDEX_YRES, height);
		vbox_write_ioport(VBE_DISPI_INDEX_VIRT_WIDTH, pitch * 8 / bpp);
		vbox_write_ioport(VBE_DISPI_INDEX_BPP,
				  CRTC_FB(crtc)->format->cpp[0] * 8);
		vbox_write_ioport(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED);
		vbox_write_ioport(
			VBE_DISPI_INDEX_X_OFFSET,
			vbox_crtc->fb_offset % pitch / bpp * 8 + crtc->x);
		vbox_write_ioport(VBE_DISPI_INDEX_Y_OFFSET,
				  vbox_crtc->fb_offset / pitch + crtc->y);
	}

	flags = VBVA_SCREEN_F_ACTIVE;
	flags |= (crtc->enabled && !vbox_crtc->blanked) ?
		 0 : VBVA_SCREEN_F_BLANK;
	flags |= vbox_crtc->disconnected ? VBVA_SCREEN_F_DISABLED : 0;
	hgsmi_process_display_info(vbox->guest_pool, vbox_crtc->crtc_id,
				   x_offset, y_offset,
				   crtc->x * bpp / 8 + crtc->y * pitch,
				   pitch, width, height,
				   vbox_crtc->blanked ? 0 : bpp, flags);
}