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
struct TYPE_2__ {scalar_t__ chain_index; } ;
struct tc_cls_matchall_offload {int command; TYPE_1__ common; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSMATCHALL_DESTROY 129 
#define  TC_CLSMATCHALL_REPLACE 128 
 int dsa_slave_add_cls_matchall (struct net_device*,struct tc_cls_matchall_offload*,int) ; 
 int /*<<< orphan*/  dsa_slave_del_cls_matchall (struct net_device*,struct tc_cls_matchall_offload*) ; 

__attribute__((used)) static int dsa_slave_setup_tc_cls_matchall(struct net_device *dev,
					   struct tc_cls_matchall_offload *cls,
					   bool ingress)
{
	if (cls->common.chain_index)
		return -EOPNOTSUPP;

	switch (cls->command) {
	case TC_CLSMATCHALL_REPLACE:
		return dsa_slave_add_cls_matchall(dev, cls, ingress);
	case TC_CLSMATCHALL_DESTROY:
		dsa_slave_del_cls_matchall(dev, cls);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}