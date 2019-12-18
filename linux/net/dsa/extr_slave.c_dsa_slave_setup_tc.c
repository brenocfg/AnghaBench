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
struct net_device {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_2__ {int (* port_setup_tc ) (struct dsa_switch*,int /*<<< orphan*/ ,int,void*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int TC_SETUP_BLOCK ; 
 int dsa_slave_setup_tc_block (struct net_device*,void*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static int dsa_slave_setup_tc(struct net_device *dev, enum tc_setup_type type,
			      void *type_data)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	if (type == TC_SETUP_BLOCK)
		return dsa_slave_setup_tc_block(dev, type_data);

	if (!ds->ops->port_setup_tc)
		return -EOPNOTSUPP;

	return ds->ops->port_setup_tc(ds, dp->index, type, type_data);
}