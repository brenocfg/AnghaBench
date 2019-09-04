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
typedef  size_t u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ sk; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int dummy; } ;
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  tx_qdid; struct dpaa2_eth_fq* fq; int /*<<< orphan*/  percpu_extras; int /*<<< orphan*/  percpu_stats; } ;
struct dpaa2_eth_fq {int /*<<< orphan*/  tx_qdbin; TYPE_1__* channel; } ;
struct dpaa2_eth_drv_stats {int tx_portal_busy; int /*<<< orphan*/  tx_sg_bytes; int /*<<< orphan*/  tx_sg_frames; int /*<<< orphan*/  tx_reallocs; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  fd ;
struct TYPE_2__ {int /*<<< orphan*/  dpio; } ;

/* Variables and functions */
 int DPAA2_ETH_ENQUEUE_RETRIES ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int build_sg_fd (struct dpaa2_eth_priv*,struct sk_buff*,struct dpaa2_fd*) ; 
 int build_single_fd (struct dpaa2_eth_priv*,struct sk_buff*,struct dpaa2_fd*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned int dpaa2_eth_needed_headroom (struct dpaa2_eth_priv*,struct sk_buff*) ; 
 scalar_t__ dpaa2_fd_get_len (struct dpaa2_fd*) ; 
 int dpaa2_io_service_enqueue_qd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpaa2_fd*) ; 
 int /*<<< orphan*/  free_tx_fd (struct dpaa2_eth_priv*,struct dpaa2_fd*) ; 
 int /*<<< orphan*/  memset (struct dpaa2_fd*,int /*<<< orphan*/ ,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpaa2_tx_fd (struct net_device*,struct dpaa2_fd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t dpaa2_eth_tx(struct sk_buff *skb, struct net_device *net_dev)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	struct dpaa2_fd fd;
	struct rtnl_link_stats64 *percpu_stats;
	struct dpaa2_eth_drv_stats *percpu_extras;
	struct dpaa2_eth_fq *fq;
	u16 queue_mapping;
	unsigned int needed_headroom;
	int err, i;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	percpu_extras = this_cpu_ptr(priv->percpu_extras);

	needed_headroom = dpaa2_eth_needed_headroom(priv, skb);
	if (skb_headroom(skb) < needed_headroom) {
		struct sk_buff *ns;

		ns = skb_realloc_headroom(skb, needed_headroom);
		if (unlikely(!ns)) {
			percpu_stats->tx_dropped++;
			goto err_alloc_headroom;
		}
		percpu_extras->tx_reallocs++;

		if (skb->sk)
			skb_set_owner_w(ns, skb->sk);

		dev_kfree_skb(skb);
		skb = ns;
	}

	/* We'll be holding a back-reference to the skb until Tx Confirmation;
	 * we don't want that overwritten by a concurrent Tx with a cloned skb.
	 */
	skb = skb_unshare(skb, GFP_ATOMIC);
	if (unlikely(!skb)) {
		/* skb_unshare() has already freed the skb */
		percpu_stats->tx_dropped++;
		return NETDEV_TX_OK;
	}

	/* Setup the FD fields */
	memset(&fd, 0, sizeof(fd));

	if (skb_is_nonlinear(skb)) {
		err = build_sg_fd(priv, skb, &fd);
		percpu_extras->tx_sg_frames++;
		percpu_extras->tx_sg_bytes += skb->len;
	} else {
		err = build_single_fd(priv, skb, &fd);
	}

	if (unlikely(err)) {
		percpu_stats->tx_dropped++;
		goto err_build_fd;
	}

	/* Tracing point */
	trace_dpaa2_tx_fd(net_dev, &fd);

	/* TxConf FQ selection relies on queue id from the stack.
	 * In case of a forwarded frame from another DPNI interface, we choose
	 * a queue affined to the same core that processed the Rx frame
	 */
	queue_mapping = skb_get_queue_mapping(skb);
	fq = &priv->fq[queue_mapping];
	for (i = 0; i < DPAA2_ETH_ENQUEUE_RETRIES; i++) {
		err = dpaa2_io_service_enqueue_qd(fq->channel->dpio,
						  priv->tx_qdid, 0,
						  fq->tx_qdbin, &fd);
		if (err != -EBUSY)
			break;
	}
	percpu_extras->tx_portal_busy += i;
	if (unlikely(err < 0)) {
		percpu_stats->tx_errors++;
		/* Clean up everything, including freeing the skb */
		free_tx_fd(priv, &fd);
	} else {
		percpu_stats->tx_packets++;
		percpu_stats->tx_bytes += dpaa2_fd_get_len(&fd);
	}

	return NETDEV_TX_OK;

err_build_fd:
err_alloc_headroom:
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}