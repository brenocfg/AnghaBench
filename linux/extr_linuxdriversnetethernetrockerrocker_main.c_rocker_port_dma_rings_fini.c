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
struct rocker_port {int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring; struct rocker* rocker; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  rocker_dma_ring_bufs_free (struct rocker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_dma_ring_destroy (struct rocker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_rx_ring_skbs_free (struct rocker_port*) ; 

__attribute__((used)) static void rocker_port_dma_rings_fini(struct rocker_port *rocker_port)
{
	struct rocker *rocker = rocker_port->rocker;

	rocker_dma_rx_ring_skbs_free(rocker_port);
	rocker_dma_ring_bufs_free(rocker, &rocker_port->rx_ring,
				  PCI_DMA_BIDIRECTIONAL);
	rocker_dma_ring_destroy(rocker, &rocker_port->rx_ring);
	rocker_dma_ring_bufs_free(rocker, &rocker_port->tx_ring,
				  PCI_DMA_TODEVICE);
	rocker_dma_ring_destroy(rocker, &rocker_port->tx_ring);
}