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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct fst_port_info {scalar_t__ index; size_t txqe; int txqs; int start; struct sk_buff** txq; struct fst_card_info* card; } ;
struct fst_card_info {scalar_t__ card_no; int /*<<< orphan*/  card_lock; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ASS ; 
 int /*<<< orphan*/  DBG_TX ; 
 int FST_TXQ_DEPTH ; 
 scalar_t__ LEN_TX_BUFFER ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct fst_port_info* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  fst_q_work_item (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fst_tx_task ; 
 int fst_txq_high ; 
 int /*<<< orphan*/  fst_work_txq ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t
fst_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct fst_card_info *card;
	struct fst_port_info *port;
	unsigned long flags;
	int txq_length;

	port = dev_to_port(dev);
	card = port->card;
	dbg(DBG_TX, "fst_start_xmit: length = %d\n", skb->len);

	/* Drop packet with error if we don't have carrier */
	if (!netif_carrier_ok(dev)) {
		dev_kfree_skb(skb);
		dev->stats.tx_errors++;
		dev->stats.tx_carrier_errors++;
		dbg(DBG_ASS,
		    "Tried to transmit but no carrier on card %d port %d\n",
		    card->card_no, port->index);
		return NETDEV_TX_OK;
	}

	/* Drop it if it's too big! MTU failure ? */
	if (skb->len > LEN_TX_BUFFER) {
		dbg(DBG_ASS, "Packet too large %d vs %d\n", skb->len,
		    LEN_TX_BUFFER);
		dev_kfree_skb(skb);
		dev->stats.tx_errors++;
		return NETDEV_TX_OK;
	}

	/*
	 * We are always going to queue the packet
	 * so that the bottom half is the only place we tx from
	 * Check there is room in the port txq
	 */
	spin_lock_irqsave(&card->card_lock, flags);
	if ((txq_length = port->txqe - port->txqs) < 0) {
		/*
		 * This is the case where the next free has wrapped but the
		 * last used hasn't
		 */
		txq_length = txq_length + FST_TXQ_DEPTH;
	}
	spin_unlock_irqrestore(&card->card_lock, flags);
	if (txq_length > fst_txq_high) {
		/*
		 * We have got enough buffers in the pipeline.  Ask the network
		 * layer to stop sending frames down
		 */
		netif_stop_queue(dev);
		port->start = 1;	/* I'm using this to signal stop sent up */
	}

	if (txq_length == FST_TXQ_DEPTH - 1) {
		/*
		 * This shouldn't have happened but such is life
		 */
		dev_kfree_skb(skb);
		dev->stats.tx_errors++;
		dbg(DBG_ASS, "Tx queue overflow card %d port %d\n",
		    card->card_no, port->index);
		return NETDEV_TX_OK;
	}

	/*
	 * queue the buffer
	 */
	spin_lock_irqsave(&card->card_lock, flags);
	port->txq[port->txqe] = skb;
	port->txqe++;
	if (port->txqe == FST_TXQ_DEPTH)
		port->txqe = 0;
	spin_unlock_irqrestore(&card->card_lock, flags);

	/* Scehdule the bottom half which now does transmit processing */
	fst_q_work_item(&fst_work_txq, card->card_no);
	tasklet_schedule(&fst_tx_task);

	return NETDEV_TX_OK;
}