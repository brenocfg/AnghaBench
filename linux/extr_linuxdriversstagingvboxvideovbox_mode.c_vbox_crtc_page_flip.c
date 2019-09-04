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
typedef  int /*<<< orphan*/  uint32_t ;
struct vbox_private {int /*<<< orphan*/  hw_mutex; struct drm_device* dev; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {int /*<<< orphan*/  mode; TYPE_1__* dev; } ;
struct TYPE_2__ {struct vbox_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_FB (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vbox_crtc_do_set_base (struct drm_crtc*,int /*<<< orphan*/ ,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_do_modeset (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbox_set_view (struct drm_crtc*) ; 

__attribute__((used)) static int vbox_crtc_page_flip(struct drm_crtc *crtc,
			       struct drm_framebuffer *fb,
			       struct drm_pending_vblank_event *event,
			       uint32_t page_flip_flags,
			       struct drm_modeset_acquire_ctx *ctx)
{
	struct vbox_private *vbox = crtc->dev->dev_private;
	struct drm_device *drm = vbox->dev;
	unsigned long flags;
	int rc;

	rc = vbox_crtc_do_set_base(crtc, CRTC_FB(crtc), fb, 0, 0);
	if (rc)
		return rc;

	mutex_lock(&vbox->hw_mutex);
	vbox_set_view(crtc);
	vbox_do_modeset(crtc, &crtc->mode);
	mutex_unlock(&vbox->hw_mutex);

	spin_lock_irqsave(&drm->event_lock, flags);

	if (event)
		drm_crtc_send_vblank_event(crtc, event);

	spin_unlock_irqrestore(&drm->event_lock, flags);

	return 0;
}