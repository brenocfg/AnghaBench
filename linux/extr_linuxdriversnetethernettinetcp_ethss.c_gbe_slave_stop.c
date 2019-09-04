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
struct gbe_slave {int port_num; int /*<<< orphan*/ * phy; } ;
struct gbe_priv {int /*<<< orphan*/  ale; } ;
struct gbe_intf {TYPE_1__* ndev; struct gbe_slave* slave; struct gbe_priv* gbe_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  broadcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_DISABLE ; 
 int /*<<< orphan*/  IS_SS_ID_2U (struct gbe_priv*) ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_del_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbe_port_reset (struct gbe_slave*) ; 
 int /*<<< orphan*/  gbe_sgmii_rtreset (struct gbe_priv*,struct gbe_slave*,int) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gbe_slave_stop(struct gbe_intf *intf)
{
	struct gbe_priv *gbe_dev = intf->gbe_dev;
	struct gbe_slave *slave = intf->slave;

	if (!IS_SS_ID_2U(gbe_dev))
		gbe_sgmii_rtreset(gbe_dev, slave, true);
	gbe_port_reset(slave);
	/* Disable forwarding */
	cpsw_ale_control_set(gbe_dev->ale, slave->port_num,
			     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);
	cpsw_ale_del_mcast(gbe_dev->ale, intf->ndev->broadcast,
			   1 << slave->port_num, 0, 0);

	if (!slave->phy)
		return;

	phy_stop(slave->phy);
	phy_disconnect(slave->phy);
	slave->phy = NULL;
}