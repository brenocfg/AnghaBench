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
struct vbox_private {int initial_mode_queried; int /*<<< orphan*/  hw_mutex; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct vbox_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbox_disable_accel (struct vbox_private*) ; 

__attribute__((used)) static int vbox_master_set(struct drm_device *dev,
			   struct drm_file *file_priv, bool from_open)
{
	struct vbox_private *vbox = dev->dev_private;

	/*
	 * We do not yet know whether the new owner can handle hotplug, so we
	 * do not advertise dynamic modes on the first query and send a
	 * tentative hotplug notification after that to see if they query again.
	 */
	vbox->initial_mode_queried = false;

	mutex_lock(&vbox->hw_mutex);
	/*
	 * Disable VBVA when someone releases master in case the next person
	 * tries tries to do VESA.
	 */
	/** @todo work out if anyone is likely to and whether it will work. */
	/*
	 * Update: we also disable it because if the new master does not do
	 * dirty rectangle reporting (e.g. old versions of Plymouth) then at
	 * least the first screen will still be updated. We enable it as soon
	 * as we receive a dirty rectangle report.
	 */
	vbox_disable_accel(vbox);
	mutex_unlock(&vbox->hw_mutex);

	return 0;
}