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
struct net_bridge_port {int dummy; } ;
struct kobject {int dummy; } ;
struct brport_attribute {int /*<<< orphan*/  (* show ) (struct net_bridge_port*,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct net_bridge_port* kobj_to_brport (struct kobject*) ; 
 int /*<<< orphan*/  stub1 (struct net_bridge_port*,char*) ; 
 struct brport_attribute* to_brport_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t brport_show(struct kobject *kobj,
			   struct attribute *attr, char *buf)
{
	struct brport_attribute *brport_attr = to_brport_attr(attr);
	struct net_bridge_port *p = kobj_to_brport(kobj);

	if (!brport_attr->show)
		return -EINVAL;

	return brport_attr->show(p, buf);
}