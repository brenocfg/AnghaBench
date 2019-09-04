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
struct sxgbe_rx_queue {int /*<<< orphan*/  rx_skbuff; int /*<<< orphan*/  rx_skbuff_dma; int /*<<< orphan*/  dma_rx_phy; int /*<<< orphan*/  dma_rx; } ;
struct sxgbe_rx_norm_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rx_ring(struct device *dev, struct sxgbe_rx_queue *rx_ring,
			 int rx_rsize)
{
	dma_free_coherent(dev, rx_rsize * sizeof(struct sxgbe_rx_norm_desc),
			  rx_ring->dma_rx, rx_ring->dma_rx_phy);
	kfree(rx_ring->rx_skbuff_dma);
	kfree(rx_ring->rx_skbuff);
}