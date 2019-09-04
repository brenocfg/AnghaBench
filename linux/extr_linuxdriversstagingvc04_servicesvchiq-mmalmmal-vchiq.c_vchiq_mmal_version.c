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
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_instance {int /*<<< orphan*/  vchiq_mutex; } ;

/* Variables and functions */
 int EINTR ; 
 int get_version (struct vchiq_mmal_instance*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int vchiq_mmal_version(struct vchiq_mmal_instance *instance,
		       u32 *major_out, u32 *minor_out)
{
	int ret;

	if (mutex_lock_interruptible(&instance->vchiq_mutex))
		return -EINTR;

	ret = get_version(instance, major_out, minor_out);

	mutex_unlock(&instance->vchiq_mutex);

	return ret;
}