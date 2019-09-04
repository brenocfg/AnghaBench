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
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 

__attribute__((used)) static int typec_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	int ret;

	ret = add_uevent_var(env, "TYPEC_PORT=%s", dev_name(dev));
	if (ret)
		dev_err(dev, "failed to add uevent TYPEC_PORT\n");

	return ret;
}