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
struct TYPE_3__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct fst_port_info {size_t index; } ;
struct fst_card_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TX ; 
 int DMA_OWN ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int) ; 
 int TX_ENP ; 
 int TX_STP ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 struct net_device* port_to_dev (struct fst_port_info*) ; 
 TYPE_2__** txDescrRing ; 

__attribute__((used)) static void
fst_tx_dma_complete(struct fst_card_info *card, struct fst_port_info *port,
		    int len, int txpos)
{
	struct net_device *dev = port_to_dev(port);

	/*
	 * Everything is now set, just tell the card to go
	 */
	dbg(DBG_TX, "fst_tx_dma_complete\n");
	FST_WRB(card, txDescrRing[port->index][txpos].bits,
		DMA_OWN | TX_STP | TX_ENP);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;
	netif_trans_update(dev);
}