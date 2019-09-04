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
typedef  int u32 ;
struct bdx_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  rxf_fifo0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int IR_LNKCHG0 ; 
 int IR_PCIE_LINK ; 
 int IR_PCIE_TOUT ; 
 int IR_RX_FREE_0 ; 
 int /*<<< orphan*/  bdx_link_changed (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_rx_alloc_skbs (struct bdx_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void bdx_isr_extra(struct bdx_priv *priv, u32 isr)
{
	if (isr & IR_RX_FREE_0) {
		bdx_rx_alloc_skbs(priv, &priv->rxf_fifo0);
		DBG("RX_FREE_0\n");
	}

	if (isr & IR_LNKCHG0)
		bdx_link_changed(priv);

	if (isr & IR_PCIE_LINK)
		netdev_err(priv->ndev, "PCI-E Link Fault\n");

	if (isr & IR_PCIE_TOUT)
		netdev_err(priv->ndev, "PCI-E Time Out\n");

}