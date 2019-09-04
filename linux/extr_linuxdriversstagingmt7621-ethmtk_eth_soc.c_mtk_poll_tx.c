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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mtk_tx_ring {int (* tx_poll ) (struct mtk_eth*,int,int*) ;scalar_t__ tx_thresh; int /*<<< orphan*/  tx_free_count; } ;
struct mtk_eth {struct mtk_tx_ring tx_ring; struct net_device** netdev; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_irq_ack (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int stub1 (struct mtk_eth*,int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtk_poll_tx(struct mtk_eth *eth, int budget, u32 tx_intr,
		       bool *tx_again)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	struct net_device *netdev = eth->netdev[0];
	int done;

	done = eth->tx_ring.tx_poll(eth, budget, tx_again);
	if (!*tx_again)
		mtk_irq_ack(eth, tx_intr);

	if (!done)
		return 0;

	smp_mb();
	if (unlikely(!netif_queue_stopped(netdev)))
		return done;

	if (atomic_read(&ring->tx_free_count) > ring->tx_thresh)
		netif_wake_queue(netdev);

	return done;
}