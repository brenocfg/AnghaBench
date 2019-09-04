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

__attribute__((used)) static void vbox_master_drop(struct drm_device *dev, struct drm_file *file_priv)
{
	struct vbox_private *vbox = dev->dev_private;

	/* See vbox_master_set() */
	vbox->initial_mode_queried = false;

	mutex_lock(&vbox->hw_mutex);
	vbox_disable_accel(vbox);
	mutex_unlock(&vbox->hw_mutex);
}