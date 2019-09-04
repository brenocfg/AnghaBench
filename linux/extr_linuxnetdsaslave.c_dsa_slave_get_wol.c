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
struct ethtool_wolinfo {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  index; int /*<<< orphan*/  pl; struct dsa_switch* ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_wol ) (struct dsa_switch*,int /*<<< orphan*/ ,struct ethtool_wolinfo*) ;} ;

/* Variables and functions */
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  phylink_ethtool_get_wol (int /*<<< orphan*/ ,struct ethtool_wolinfo*) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int /*<<< orphan*/ ,struct ethtool_wolinfo*) ; 

__attribute__((used)) static void dsa_slave_get_wol(struct net_device *dev, struct ethtool_wolinfo *w)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	phylink_ethtool_get_wol(dp->pl, w);

	if (ds->ops->get_wol)
		ds->ops->get_wol(ds, dp->index, w);
}