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
struct vchiq_mmal_port {int /*<<< orphan*/  enabled; } ;
struct vchiq_mmal_instance {int /*<<< orphan*/  vchiq_mutex; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int port_disable (struct vchiq_mmal_instance*,struct vchiq_mmal_port*) ; 

int vchiq_mmal_port_disable(struct vchiq_mmal_instance *instance,
			    struct vchiq_mmal_port *port)
{
	int ret;

	if (mutex_lock_interruptible(&instance->vchiq_mutex))
		return -EINTR;

	if (!port->enabled) {
		mutex_unlock(&instance->vchiq_mutex);
		return 0;
	}

	ret = port_disable(instance, port);

	mutex_unlock(&instance->vchiq_mutex);

	return ret;
}