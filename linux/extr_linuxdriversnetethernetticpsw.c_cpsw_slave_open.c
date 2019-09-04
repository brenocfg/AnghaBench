#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct phy_device {int /*<<< orphan*/  interface; } ;
struct cpsw_slave {int /*<<< orphan*/  slave_num; struct phy_device* phy; TYPE_3__* data; scalar_t__ mac_control; TYPE_1__* sliver; } ;
struct cpsw_priv {int /*<<< orphan*/  dev; TYPE_4__* ndev; struct cpsw_common* cpsw; } ;
struct TYPE_7__ {scalar_t__ dual_emac; } ;
struct cpsw_common {int version; int /*<<< orphan*/  dev; int /*<<< orphan*/  ale; TYPE_2__ data; int /*<<< orphan*/  rx_packet_max; } ;
struct TYPE_9__ {int /*<<< orphan*/  broadcast; } ;
struct TYPE_8__ {int /*<<< orphan*/  phy_id; int /*<<< orphan*/  phy_if; scalar_t__ phy_node; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_maxlen; int /*<<< orphan*/  rx_pri_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_MCAST_FWD_2 ; 
 int /*<<< orphan*/  CPSW1_MAX_BLKS ; 
 int /*<<< orphan*/  CPSW1_TX_PRI_MAP ; 
 int /*<<< orphan*/  CPSW2_MAX_BLKS ; 
 int /*<<< orphan*/  CPSW2_TX_PRI_MAP ; 
 int CPSW_MAX_BLKS_RX ; 
 int CPSW_MAX_BLKS_TX ; 
 int CPSW_MAX_BLKS_TX_SHIFT ; 
#define  CPSW_VERSION_1 131 
#define  CPSW_VERSION_2 130 
#define  CPSW_VERSION_3 129 
#define  CPSW_VERSION_4 128 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  RX_PRIORITY_MAPPING ; 
 int TX_PRIORITY_MAPPING ; 
 int /*<<< orphan*/  cpsw_add_dual_emac_def_ale_entries (struct cpsw_priv*,struct cpsw_slave*,int) ; 
 int /*<<< orphan*/  cpsw_adjust_link ; 
 int /*<<< orphan*/  cpsw_ale_add_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpsw_get_slave_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_phy_sel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_set_slave_mac (struct cpsw_slave*,struct cpsw_priv*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct phy_device* of_phy_connect (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int /*<<< orphan*/  slave_write (struct cpsw_slave*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_reset_slave (struct cpsw_slave*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpsw_slave_open(struct cpsw_slave *slave, struct cpsw_priv *priv)
{
	u32 slave_port;
	struct phy_device *phy;
	struct cpsw_common *cpsw = priv->cpsw;

	soft_reset_slave(slave);

	/* setup priority mapping */
	writel_relaxed(RX_PRIORITY_MAPPING, &slave->sliver->rx_pri_map);

	switch (cpsw->version) {
	case CPSW_VERSION_1:
		slave_write(slave, TX_PRIORITY_MAPPING, CPSW1_TX_PRI_MAP);
		/* Increase RX FIFO size to 5 for supporting fullduplex
		 * flow control mode
		 */
		slave_write(slave,
			    (CPSW_MAX_BLKS_TX << CPSW_MAX_BLKS_TX_SHIFT) |
			    CPSW_MAX_BLKS_RX, CPSW1_MAX_BLKS);
		break;
	case CPSW_VERSION_2:
	case CPSW_VERSION_3:
	case CPSW_VERSION_4:
		slave_write(slave, TX_PRIORITY_MAPPING, CPSW2_TX_PRI_MAP);
		/* Increase RX FIFO size to 5 for supporting fullduplex
		 * flow control mode
		 */
		slave_write(slave,
			    (CPSW_MAX_BLKS_TX << CPSW_MAX_BLKS_TX_SHIFT) |
			    CPSW_MAX_BLKS_RX, CPSW2_MAX_BLKS);
		break;
	}

	/* setup max packet size, and mac address */
	writel_relaxed(cpsw->rx_packet_max, &slave->sliver->rx_maxlen);
	cpsw_set_slave_mac(slave, priv);

	slave->mac_control = 0;	/* no link yet */

	slave_port = cpsw_get_slave_port(slave->slave_num);

	if (cpsw->data.dual_emac)
		cpsw_add_dual_emac_def_ale_entries(priv, slave, slave_port);
	else
		cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
				   1 << slave_port, 0, 0, ALE_MCAST_FWD_2);

	if (slave->data->phy_node) {
		phy = of_phy_connect(priv->ndev, slave->data->phy_node,
				 &cpsw_adjust_link, 0, slave->data->phy_if);
		if (!phy) {
			dev_err(priv->dev, "phy \"%pOF\" not found on slave %d\n",
				slave->data->phy_node,
				slave->slave_num);
			return;
		}
	} else {
		phy = phy_connect(priv->ndev, slave->data->phy_id,
				 &cpsw_adjust_link, slave->data->phy_if);
		if (IS_ERR(phy)) {
			dev_err(priv->dev,
				"phy \"%s\" not found on slave %d, err %ld\n",
				slave->data->phy_id, slave->slave_num,
				PTR_ERR(phy));
			return;
		}
	}

	slave->phy = phy;

	phy_attached_info(slave->phy);

	phy_start(slave->phy);

	/* Configure GMII_SEL register */
	cpsw_phy_sel(cpsw->dev, slave->phy->interface, slave->slave_num);
}