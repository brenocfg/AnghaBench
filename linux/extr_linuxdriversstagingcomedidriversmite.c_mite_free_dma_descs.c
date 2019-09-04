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
struct mite_ring {int n_links; int /*<<< orphan*/  dma_addr; struct mite_dma_desc* descs; int /*<<< orphan*/  hw_dev; } ;
struct mite_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct mite_dma_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mite_free_dma_descs(struct mite_ring *ring)
{
	struct mite_dma_desc *descs = ring->descs;

	if (descs) {
		dma_free_coherent(ring->hw_dev,
				  ring->n_links * sizeof(*descs),
				  descs, ring->dma_addr);
		ring->descs = NULL;
		ring->dma_addr = 0;
		ring->n_links = 0;
	}
}