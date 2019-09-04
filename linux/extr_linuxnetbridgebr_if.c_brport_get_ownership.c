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
struct net_bridge_port {int /*<<< orphan*/  dev; } ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct net_bridge_port* kobj_to_brport (struct kobject*) ; 
 int /*<<< orphan*/  net_ns_get_ownership (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brport_get_ownership(struct kobject *kobj, kuid_t *uid, kgid_t *gid)
{
	struct net_bridge_port *p = kobj_to_brport(kobj);

	net_ns_get_ownership(dev_net(p->dev), uid, gid);
}