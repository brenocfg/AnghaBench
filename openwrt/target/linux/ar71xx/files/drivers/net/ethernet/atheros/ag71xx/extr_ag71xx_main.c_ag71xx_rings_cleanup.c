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
struct ag71xx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_ring_rx_clean (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_ring_tx_clean (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_rings_free (struct ag71xx*) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ag71xx_rings_cleanup(struct ag71xx *ag)
{
	ag71xx_ring_rx_clean(ag);
	ag71xx_ring_tx_clean(ag);
	ag71xx_rings_free(ag);

	netdev_reset_queue(ag->dev);
}