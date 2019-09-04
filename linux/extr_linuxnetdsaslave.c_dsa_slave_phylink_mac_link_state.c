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
struct phylink_link_state {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
struct TYPE_2__ {int (* phylink_mac_link_state ) (struct dsa_switch*,int /*<<< orphan*/ ,struct phylink_link_state*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,struct phylink_link_state*) ; 

__attribute__((used)) static int dsa_slave_phylink_mac_link_state(struct net_device *dev,
					    struct phylink_link_state *state)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	/* Only called for SGMII and 802.3z */
	if (!ds->ops->phylink_mac_link_state)
		return -EOPNOTSUPP;

	return ds->ops->phylink_mac_link_state(ds, dp->index, state);
}