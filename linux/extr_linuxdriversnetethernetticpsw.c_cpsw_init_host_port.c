#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cpsw_priv {TYPE_4__* ndev; int /*<<< orphan*/  mac_addr; struct cpsw_common* cpsw; } ;
struct TYPE_7__ {scalar_t__ dual_emac; } ;
struct cpsw_common {int /*<<< orphan*/  ale; TYPE_3__ data; TYPE_2__* host_port_regs; TYPE_1__* regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  broadcast; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpdma_rx_chan_map; int /*<<< orphan*/  cpdma_tx_pri_map; int /*<<< orphan*/  tx_in_ctl; } ;
struct TYPE_5__ {int /*<<< orphan*/  control; int /*<<< orphan*/  soft_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_MCAST_FWD_2 ; 
 int /*<<< orphan*/  ALE_PORT_HOST ; 
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_FORWARD ; 
 int /*<<< orphan*/  ALE_VLAN_AWARE ; 
 int /*<<< orphan*/  CPDMA_TX_PRIORITY_MAP ; 
 int /*<<< orphan*/  CPSW_ALE_VLAN_AWARE ; 
 int CPSW_FIFO_DUAL_MAC_MODE ; 
 int CPSW_FIFO_NORMAL_MODE ; 
 int CPSW_RX_VLAN_ENCAP ; 
 int CPSW_VLAN_AWARE ; 
 int /*<<< orphan*/  HOST_PORT_NUM ; 
 int /*<<< orphan*/  cpsw_ale_add_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_add_ucast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_start (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soft_reset (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpsw_init_host_port(struct cpsw_priv *priv)
{
	u32 fifo_mode;
	u32 control_reg;
	struct cpsw_common *cpsw = priv->cpsw;

	/* soft reset the controller and initialize ale */
	soft_reset("cpsw", &cpsw->regs->soft_reset);
	cpsw_ale_start(cpsw->ale);

	/* switch to vlan unaware mode */
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_VLAN_AWARE,
			     CPSW_ALE_VLAN_AWARE);
	control_reg = readl(&cpsw->regs->control);
	control_reg |= CPSW_VLAN_AWARE | CPSW_RX_VLAN_ENCAP;
	writel(control_reg, &cpsw->regs->control);
	fifo_mode = (cpsw->data.dual_emac) ? CPSW_FIFO_DUAL_MAC_MODE :
		     CPSW_FIFO_NORMAL_MODE;
	writel(fifo_mode, &cpsw->host_port_regs->tx_in_ctl);

	/* setup host port priority mapping */
	writel_relaxed(CPDMA_TX_PRIORITY_MAP,
		       &cpsw->host_port_regs->cpdma_tx_pri_map);
	writel_relaxed(0, &cpsw->host_port_regs->cpdma_rx_chan_map);

	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

	if (!cpsw->data.dual_emac) {
		cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr, HOST_PORT_NUM,
				   0, 0);
		cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
				   ALE_PORT_HOST, 0, 0, ALE_MCAST_FWD_2);
	}
}