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
struct vbox_crtc {unsigned int crtc_id; int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int) ; 
 struct vbox_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_crtc_funcs ; 
 int /*<<< orphan*/  vbox_crtc_helper_funcs ; 

__attribute__((used)) static struct vbox_crtc *vbox_crtc_init(struct drm_device *dev, unsigned int i)
{
	struct vbox_crtc *vbox_crtc;

	vbox_crtc = kzalloc(sizeof(*vbox_crtc), GFP_KERNEL);
	if (!vbox_crtc)
		return NULL;

	vbox_crtc->crtc_id = i;

	drm_crtc_init(dev, &vbox_crtc->base, &vbox_crtc_funcs);
	drm_mode_crtc_set_gamma_size(&vbox_crtc->base, 256);
	drm_crtc_helper_add(&vbox_crtc->base, &vbox_crtc_helper_funcs);

	return vbox_crtc;
}