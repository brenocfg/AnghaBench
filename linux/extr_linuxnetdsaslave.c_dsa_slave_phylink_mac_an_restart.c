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
struct TYPE_2__ {int /*<<< orphan*/  (* phylink_mac_an_restart ) (struct dsa_switch*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsa_slave_phylink_mac_an_restart(struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	if (!ds->ops->phylink_mac_an_restart)
		return;

	ds->ops->phylink_mac_an_restart(ds, dp->index);
}