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
struct typec_altmode {int /*<<< orphan*/  mode; int /*<<< orphan*/  svid; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,...) ; 
 struct typec_altmode* to_typec_altmode (struct device*) ; 

__attribute__((used)) static int typec_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct typec_altmode *altmode = to_typec_altmode(dev);

	if (add_uevent_var(env, "SVID=%04X", altmode->svid))
		return -ENOMEM;

	if (add_uevent_var(env, "MODE=%u", altmode->mode))
		return -ENOMEM;

	return add_uevent_var(env, "MODALIAS=typec:id%04Xm%02X",
			      altmode->svid, altmode->mode);
}