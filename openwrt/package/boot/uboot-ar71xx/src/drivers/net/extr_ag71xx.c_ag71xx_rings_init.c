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
struct ag71xx {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_RX_RING_SIZE ; 
 int /*<<< orphan*/  AG71XX_TX_RING_SIZE ; 
 int ag71xx_ring_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ag71xx_ring_rx_init (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_ring_tx_init (struct ag71xx*) ; 

__attribute__((used)) static int ag71xx_rings_init(struct ag71xx *ag)
{
	int ret;

	ret = ag71xx_ring_alloc(&ag->tx_ring, AG71XX_TX_RING_SIZE);
	if (ret)
		return ret;

	ag71xx_ring_tx_init(ag);

	ret = ag71xx_ring_alloc(&ag->rx_ring, AG71XX_RX_RING_SIZE);
	if (ret)
		return ret;

	ret = ag71xx_ring_rx_init(ag);
	return ret;
}