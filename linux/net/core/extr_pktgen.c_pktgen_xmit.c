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
struct sk_buff {int /*<<< orphan*/  users; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  len; } ;
struct pktgen_dev {scalar_t__ delay; int last_ok; scalar_t__ clone_count; scalar_t__ clone_skb; scalar_t__ xmit_mode; scalar_t__ sofar; scalar_t__ count; struct sk_buff* skb; int /*<<< orphan*/  errors; int /*<<< orphan*/  odevname; int /*<<< orphan*/  last_pkt_size; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  next_tx; struct net_device* odev; int /*<<< orphan*/  burst; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARD_TX_LOCK (struct net_device*,struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HARD_TX_UNLOCK (struct net_device*,struct netdev_queue*) ; 
 scalar_t__ M_NETIF_RECEIVE ; 
 scalar_t__ M_QUEUE_XMIT ; 
#define  NETDEV_TX_BUSY 132 
#define  NETDEV_TX_OK 131 
 int NET_RX_DROP ; 
#define  NET_XMIT_CN 130 
#define  NET_XMIT_DROP 129 
#define  NET_XMIT_SUCCESS 128 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ULLONG_MAX ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* fill_packet (struct net_device*,struct pktgen_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ ,int) ; 
 int netdev_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 unsigned int netif_xmit_frozen_or_drv_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  pktgen_stop_device (struct pktgen_dev*) ; 
 int /*<<< orphan*/  pktgen_wait_for_skb (struct pktgen_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  refcount_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 unsigned int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_sub_and_test (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 struct netdev_queue* skb_get_tx_queue (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_tc (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin (struct pktgen_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void pktgen_xmit(struct pktgen_dev *pkt_dev)
{
	unsigned int burst = READ_ONCE(pkt_dev->burst);
	struct net_device *odev = pkt_dev->odev;
	struct netdev_queue *txq;
	struct sk_buff *skb;
	int ret;

	/* If device is offline, then don't send */
	if (unlikely(!netif_running(odev) || !netif_carrier_ok(odev))) {
		pktgen_stop_device(pkt_dev);
		return;
	}

	/* This is max DELAY, this has special meaning of
	 * "never transmit"
	 */
	if (unlikely(pkt_dev->delay == ULLONG_MAX)) {
		pkt_dev->next_tx = ktime_add_ns(ktime_get(), ULONG_MAX);
		return;
	}

	/* If no skb or clone count exhausted then get new one */
	if (!pkt_dev->skb || (pkt_dev->last_ok &&
			      ++pkt_dev->clone_count >= pkt_dev->clone_skb)) {
		/* build a new pkt */
		kfree_skb(pkt_dev->skb);

		pkt_dev->skb = fill_packet(odev, pkt_dev);
		if (pkt_dev->skb == NULL) {
			pr_err("ERROR: couldn't allocate skb in fill_packet\n");
			schedule();
			pkt_dev->clone_count--;	/* back out increment, OOM */
			return;
		}
		pkt_dev->last_pkt_size = pkt_dev->skb->len;
		pkt_dev->clone_count = 0;	/* reset counter */
	}

	if (pkt_dev->delay && pkt_dev->last_ok)
		spin(pkt_dev, pkt_dev->next_tx);

	if (pkt_dev->xmit_mode == M_NETIF_RECEIVE) {
		skb = pkt_dev->skb;
		skb->protocol = eth_type_trans(skb, skb->dev);
		refcount_add(burst, &skb->users);
		local_bh_disable();
		do {
			ret = netif_receive_skb(skb);
			if (ret == NET_RX_DROP)
				pkt_dev->errors++;
			pkt_dev->sofar++;
			pkt_dev->seq_num++;
			if (refcount_read(&skb->users) != burst) {
				/* skb was queued by rps/rfs or taps,
				 * so cannot reuse this skb
				 */
				WARN_ON(refcount_sub_and_test(burst - 1, &skb->users));
				/* get out of the loop and wait
				 * until skb is consumed
				 */
				break;
			}
			/* skb was 'freed' by stack, so clean few
			 * bits and reuse it
			 */
			skb_reset_tc(skb);
		} while (--burst > 0);
		goto out; /* Skips xmit_mode M_START_XMIT */
	} else if (pkt_dev->xmit_mode == M_QUEUE_XMIT) {
		local_bh_disable();
		refcount_inc(&pkt_dev->skb->users);

		ret = dev_queue_xmit(pkt_dev->skb);
		switch (ret) {
		case NET_XMIT_SUCCESS:
			pkt_dev->sofar++;
			pkt_dev->seq_num++;
			pkt_dev->tx_bytes += pkt_dev->last_pkt_size;
			break;
		case NET_XMIT_DROP:
		case NET_XMIT_CN:
		/* These are all valid return codes for a qdisc but
		 * indicate packets are being dropped or will likely
		 * be dropped soon.
		 */
		case NETDEV_TX_BUSY:
		/* qdisc may call dev_hard_start_xmit directly in cases
		 * where no queues exist e.g. loopback device, virtual
		 * devices, etc. In this case we need to handle
		 * NETDEV_TX_ codes.
		 */
		default:
			pkt_dev->errors++;
			net_info_ratelimited("%s xmit error: %d\n",
					     pkt_dev->odevname, ret);
			break;
		}
		goto out;
	}

	txq = skb_get_tx_queue(odev, pkt_dev->skb);

	local_bh_disable();

	HARD_TX_LOCK(odev, txq, smp_processor_id());

	if (unlikely(netif_xmit_frozen_or_drv_stopped(txq))) {
		ret = NETDEV_TX_BUSY;
		pkt_dev->last_ok = 0;
		goto unlock;
	}
	refcount_add(burst, &pkt_dev->skb->users);

xmit_more:
	ret = netdev_start_xmit(pkt_dev->skb, odev, txq, --burst > 0);

	switch (ret) {
	case NETDEV_TX_OK:
		pkt_dev->last_ok = 1;
		pkt_dev->sofar++;
		pkt_dev->seq_num++;
		pkt_dev->tx_bytes += pkt_dev->last_pkt_size;
		if (burst > 0 && !netif_xmit_frozen_or_drv_stopped(txq))
			goto xmit_more;
		break;
	case NET_XMIT_DROP:
	case NET_XMIT_CN:
		/* skb has been consumed */
		pkt_dev->errors++;
		break;
	default: /* Drivers are not supposed to return other values! */
		net_info_ratelimited("%s xmit error: %d\n",
				     pkt_dev->odevname, ret);
		pkt_dev->errors++;
		/* fall through */
	case NETDEV_TX_BUSY:
		/* Retry it next time */
		refcount_dec(&(pkt_dev->skb->users));
		pkt_dev->last_ok = 0;
	}
	if (unlikely(burst))
		WARN_ON(refcount_sub_and_test(burst, &pkt_dev->skb->users));
unlock:
	HARD_TX_UNLOCK(odev, txq);

out:
	local_bh_enable();

	/* If pkt_dev->count is zero, then run forever */
	if ((pkt_dev->count != 0) && (pkt_dev->sofar >= pkt_dev->count)) {
		pktgen_wait_for_skb(pkt_dev);

		/* Done with this */
		pktgen_stop_device(pkt_dev);
	}
}