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
struct rocker_dma_ring_info {int size; int /*<<< orphan*/ * desc_info; } ;
struct rocker_port {struct rocker* rocker; struct rocker_dma_ring_info rx_ring; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rocker_dma_rx_ring_skb_free (struct rocker const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rocker_dma_rx_ring_skbs_free(const struct rocker_port *rocker_port)
{
	const struct rocker_dma_ring_info *rx_ring = &rocker_port->rx_ring;
	const struct rocker *rocker = rocker_port->rocker;
	int i;

	for (i = 0; i < rx_ring->size; i++)
		rocker_dma_rx_ring_skb_free(rocker, &rx_ring->desc_info[i]);
}