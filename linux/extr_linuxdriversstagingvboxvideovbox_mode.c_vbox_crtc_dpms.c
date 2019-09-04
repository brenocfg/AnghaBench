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
struct vbox_private {int /*<<< orphan*/  hw_mutex; } ;
struct vbox_crtc {int blanked; } ;
struct drm_crtc {int /*<<< orphan*/  hwmode; TYPE_1__* dev; } ;
struct TYPE_2__ {struct vbox_private* dev_private; } ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vbox_crtc* to_vbox_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vbox_do_modeset (struct drm_crtc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vbox_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct vbox_crtc *vbox_crtc = to_vbox_crtc(crtc);
	struct vbox_private *vbox = crtc->dev->dev_private;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		vbox_crtc->blanked = false;
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		vbox_crtc->blanked = true;
		break;
	}

	mutex_lock(&vbox->hw_mutex);
	vbox_do_modeset(crtc, &crtc->hwmode);
	mutex_unlock(&vbox->hw_mutex);
}