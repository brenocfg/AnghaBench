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
struct channel_data {int /*<<< orphan*/ * rx_skb; TYPE_2__* netdev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dev_alloc_skb (int) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_trans_update (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 char* skb_put (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *cosa_net_setup_rx(struct channel_data *chan, int size)
{
	/*
	 * We can safely fall back to non-dma-able memory, because we have
	 * the cosa->bouncebuf pre-allocated.
	 */
	kfree_skb(chan->rx_skb);
	chan->rx_skb = dev_alloc_skb(size);
	if (chan->rx_skb == NULL) {
		pr_notice("%s: Memory squeeze, dropping packet\n", chan->name);
		chan->netdev->stats.rx_dropped++;
		return NULL;
	}
	netif_trans_update(chan->netdev);
	return skb_put(chan->rx_skb, size);
}