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
struct rocker {int /*<<< orphan*/  cmd_ring; int /*<<< orphan*/  event_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  rocker_dma_cmd_ring_waits_free (struct rocker*) ; 
 int /*<<< orphan*/  rocker_dma_ring_bufs_free (struct rocker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_dma_ring_destroy (struct rocker*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rocker_dma_rings_fini(struct rocker *rocker)
{
	rocker_dma_ring_bufs_free(rocker, &rocker->event_ring,
				  PCI_DMA_BIDIRECTIONAL);
	rocker_dma_ring_destroy(rocker, &rocker->event_ring);
	rocker_dma_cmd_ring_waits_free(rocker);
	rocker_dma_ring_bufs_free(rocker, &rocker->cmd_ring,
				  PCI_DMA_BIDIRECTIONAL);
	rocker_dma_ring_destroy(rocker, &rocker->cmd_ring);
}