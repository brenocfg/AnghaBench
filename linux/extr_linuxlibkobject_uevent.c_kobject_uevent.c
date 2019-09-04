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
struct kobject {int dummy; } ;
typedef  enum kobject_action { ____Placeholder_kobject_action } kobject_action ;

/* Variables and functions */
 int kobject_uevent_env (struct kobject*,int,int /*<<< orphan*/ *) ; 

int kobject_uevent(struct kobject *kobj, enum kobject_action action)
{
	return kobject_uevent_env(kobj, action, NULL);
}