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
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int sysfs_do_create_link_sd (struct kernfs_node*,struct kobject*,char const*,int) ; 

int sysfs_create_link_sd(struct kernfs_node *kn, struct kobject *target,
			 const char *name)
{
	return sysfs_do_create_link_sd(kn, target, name, 1);
}