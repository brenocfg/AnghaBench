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
struct vbox_private {int /*<<< orphan*/  hw_mutex; int /*<<< orphan*/  input_mapping_height; int /*<<< orphan*/  input_mapping_width; int /*<<< orphan*/  guest_pool; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct vbox_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  hgsmi_update_input_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbox_crtc_mode_set_base (struct drm_crtc*,int,int,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  vbox_do_modeset (struct drm_crtc*,struct drm_display_mode*) ; 
 int vbox_set_view (struct drm_crtc*) ; 

__attribute__((used)) static int vbox_crtc_mode_set(struct drm_crtc *crtc,
			      struct drm_display_mode *mode,
			      struct drm_display_mode *adjusted_mode,
			      int x, int y, struct drm_framebuffer *old_fb)
{
	struct vbox_private *vbox = crtc->dev->dev_private;
	int ret;

	vbox_crtc_mode_set_base(crtc, x, y, old_fb);

	mutex_lock(&vbox->hw_mutex);
	ret = vbox_set_view(crtc);
	if (!ret)
		vbox_do_modeset(crtc, mode);
	hgsmi_update_input_mapping(vbox->guest_pool, 0, 0,
				   vbox->input_mapping_width,
				   vbox->input_mapping_height);
	mutex_unlock(&vbox->hw_mutex);

	return ret;
}