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
typedef  int /*<<< orphan*/  u16 ;
struct tlan_priv {int tlan_rev; int tx_head; scalar_t__ tx_in_progress; scalar_t__ tx_list_dma; struct tlan_list* tx_list; int /*<<< orphan*/  tx_tail; } ;
struct tlan_list {int c_stat; } ;
struct net_device {scalar_t__ base_addr; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ TLAN_CH_PARM ; 
 int TLAN_CSTAT_READY ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_TX ; 
 int TLAN_HC_GO ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 tlan_handle_tx_eoc(struct net_device *dev, u16 host_int)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	struct tlan_list		*head_list;
	dma_addr_t		head_list_phys;
	u32			ack = 1;

	if (priv->tlan_rev < 0x30) {
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  handling TX EOC (Head=%d Tail=%d) -- IRQ\n",
			 priv->tx_head, priv->tx_tail);
		head_list = priv->tx_list + priv->tx_head;
		head_list_phys = priv->tx_list_dma
			+ sizeof(struct tlan_list)*priv->tx_head;
		if ((head_list->c_stat & TLAN_CSTAT_READY)
		    == TLAN_CSTAT_READY) {
			netif_stop_queue(dev);
			outl(head_list_phys, dev->base_addr + TLAN_CH_PARM);
			ack |= TLAN_HC_GO;
		} else {
			priv->tx_in_progress = 0;
		}
	}

	return ack;

}