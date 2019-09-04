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
struct visor_device {int /*<<< orphan*/  visorchannel; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/  const*) ; 
 struct visor_device* to_visor_device (struct device*) ; 
 int /*<<< orphan*/ * visorchannel_get_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visorbus_uevent(struct device *xdev, struct kobj_uevent_env *env)
{
	struct visor_device *dev;
	const guid_t *guid;

	dev = to_visor_device(xdev);
	guid = visorchannel_get_guid(dev->visorchannel);
	return add_uevent_var(env, "MODALIAS=visorbus:%pUl", guid);
}