#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {int speed; scalar_t__ duplex; scalar_t__ link; } ;
struct cpsw_slave {int /*<<< orphan*/  mac_control; TYPE_2__* sliver; struct phy_device* phy; int /*<<< orphan*/  slave_num; } ;
struct cpsw_priv {scalar_t__ shp_cfg_speed; int /*<<< orphan*/  dev; scalar_t__ tx_pause; scalar_t__ rx_pause; struct cpsw_common* cpsw; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_control; } ;
struct cpsw_common {int /*<<< orphan*/  ale; TYPE_1__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_DISABLE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_FORWARD ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_get_slave_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_shp_is_off (struct cpsw_priv*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ phy_interface_is_rgmii (struct phy_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _cpsw_adjust_link(struct cpsw_slave *slave,
			      struct cpsw_priv *priv, bool *link)
{
	struct phy_device	*phy = slave->phy;
	u32			mac_control = 0;
	u32			slave_port;
	struct cpsw_common *cpsw = priv->cpsw;

	if (!phy)
		return;

	slave_port = cpsw_get_slave_port(slave->slave_num);

	if (phy->link) {
		mac_control = cpsw->data.mac_control;

		/* enable forwarding */
		cpsw_ale_control_set(cpsw->ale, slave_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

		if (phy->speed == 1000)
			mac_control |= BIT(7);	/* GIGABITEN	*/
		if (phy->duplex)
			mac_control |= BIT(0);	/* FULLDUPLEXEN	*/

		/* set speed_in input in case RMII mode is used in 100Mbps */
		if (phy->speed == 100)
			mac_control |= BIT(15);
		/* in band mode only works in 10Mbps RGMII mode */
		else if ((phy->speed == 10) && phy_interface_is_rgmii(phy))
			mac_control |= BIT(18); /* In Band mode */

		if (priv->rx_pause)
			mac_control |= BIT(3);

		if (priv->tx_pause)
			mac_control |= BIT(4);

		*link = true;

		if (priv->shp_cfg_speed &&
		    priv->shp_cfg_speed != slave->phy->speed &&
		    !cpsw_shp_is_off(priv))
			dev_warn(priv->dev,
				 "Speed was changed, CBS shaper speeds are changed!");
	} else {
		mac_control = 0;
		/* disable forwarding */
		cpsw_ale_control_set(cpsw->ale, slave_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);
	}

	if (mac_control != slave->mac_control) {
		phy_print_status(phy);
		writel_relaxed(mac_control, &slave->sliver->mac_control);
	}

	slave->mac_control = mac_control;
}