#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; } ;
struct rocker_port {int /*<<< orphan*/  tx_ring; TYPE_2__* dev; struct rocker* rocker; } ;
struct rocker_desc_info {int dummy; } ;
struct rocker {int dummy; } ;
struct napi_struct {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,int) ; 
 scalar_t__ netif_queue_stopped (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_2__*) ; 
 struct sk_buff* rocker_desc_cookie_ptr_get (struct rocker_desc_info const*) ; 
 int rocker_desc_err (struct rocker_desc_info const*) ; 
 struct rocker_desc_info* rocker_desc_tail_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_ring_credits_set (struct rocker const*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct rocker_port* rocker_port_napi_tx_get (struct napi_struct*) ; 
 int /*<<< orphan*/  rocker_tx_desc_frags_unmap (struct rocker_port*,struct rocker_desc_info const*) ; 

__attribute__((used)) static int rocker_port_poll_tx(struct napi_struct *napi, int budget)
{
	struct rocker_port *rocker_port = rocker_port_napi_tx_get(napi);
	const struct rocker *rocker = rocker_port->rocker;
	const struct rocker_desc_info *desc_info;
	u32 credits = 0;
	int err;

	/* Cleanup tx descriptors */
	while ((desc_info = rocker_desc_tail_get(&rocker_port->tx_ring))) {
		struct sk_buff *skb;

		err = rocker_desc_err(desc_info);
		if (err && net_ratelimit())
			netdev_err(rocker_port->dev, "tx desc received with err %d\n",
				   err);
		rocker_tx_desc_frags_unmap(rocker_port, desc_info);

		skb = rocker_desc_cookie_ptr_get(desc_info);
		if (err == 0) {
			rocker_port->dev->stats.tx_packets++;
			rocker_port->dev->stats.tx_bytes += skb->len;
		} else {
			rocker_port->dev->stats.tx_errors++;
		}

		dev_kfree_skb_any(skb);
		credits++;
	}

	if (credits && netif_queue_stopped(rocker_port->dev))
		netif_wake_queue(rocker_port->dev);

	napi_complete(napi);
	rocker_dma_ring_credits_set(rocker, &rocker_port->tx_ring, credits);

	return 0;
}