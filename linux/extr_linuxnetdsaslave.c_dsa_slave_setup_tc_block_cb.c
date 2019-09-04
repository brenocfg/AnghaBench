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
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSMATCHALL 128 
 int dsa_slave_setup_tc_cls_matchall (struct net_device*,void*,int) ; 
 int /*<<< orphan*/  tc_can_offload (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				       void *cb_priv, bool ingress)
{
	struct net_device *dev = cb_priv;

	if (!tc_can_offload(dev))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSMATCHALL:
		return dsa_slave_setup_tc_cls_matchall(dev, type_data, ingress);
	default:
		return -EOPNOTSUPP;
	}
}