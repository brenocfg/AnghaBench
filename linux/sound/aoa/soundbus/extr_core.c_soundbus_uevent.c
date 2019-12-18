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
struct TYPE_2__ {int of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct soundbus_dev {int modalias; struct platform_device ofdev; } ;
struct kobj_uevent_env {int buflen; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int add_uevent_var (struct kobj_uevent_env*,char*,int,...) ; 
 char* of_get_property (int,char*,int*) ; 
 int of_node_get_device_type (int) ; 
 struct soundbus_dev* to_soundbus_device (struct device*) ; 

__attribute__((used)) static int soundbus_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct soundbus_dev * soundbus_dev;
	struct platform_device * of;
	const char *compat;
	int retval = 0;
	int cplen, seen = 0;

	if (!dev)
		return -ENODEV;

	soundbus_dev = to_soundbus_device(dev);
	if (!soundbus_dev)
		return -ENODEV;

	of = &soundbus_dev->ofdev;

	/* stuff we want to pass to /sbin/hotplug */
	retval = add_uevent_var(env, "OF_NAME=%pOFn", of->dev.of_node);
	if (retval)
		return retval;

	retval = add_uevent_var(env, "OF_TYPE=%s", of_node_get_device_type(of->dev.of_node));
	if (retval)
		return retval;

	/* Since the compatible field can contain pretty much anything
	 * it's not really legal to split it out with commas. We split it
	 * up using a number of environment variables instead. */

	compat = of_get_property(of->dev.of_node, "compatible", &cplen);
	while (compat && cplen > 0) {
		int tmp = env->buflen;
		retval = add_uevent_var(env, "OF_COMPATIBLE_%d=%s", seen, compat);
		if (retval)
			return retval;
		compat += env->buflen - tmp;
		cplen -= env->buflen - tmp;
		seen += 1;
	}

	retval = add_uevent_var(env, "OF_COMPATIBLE_N=%d", seen);
	if (retval)
		return retval;
	retval = add_uevent_var(env, "MODALIAS=%s", soundbus_dev->modalias);

	return retval;
}