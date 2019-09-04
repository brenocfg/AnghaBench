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
struct xlgmac_ring {unsigned int dma_desc_count; int /*<<< orphan*/  desc_data_head; int /*<<< orphan*/  dma_desc_head_addr; int /*<<< orphan*/  dma_desc_head; } ;
struct xlgmac_pdata {int /*<<< orphan*/  netdev; int /*<<< orphan*/  dev; } ;
struct xlgmac_dma_desc {int dummy; } ;
struct xlgmac_desc_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_init_ring(struct xlgmac_pdata *pdata,
			    struct xlgmac_ring *ring,
			    unsigned int dma_desc_count)
{
	if (!ring)
		return 0;

	/* Descriptors */
	ring->dma_desc_count = dma_desc_count;
	ring->dma_desc_head = dma_alloc_coherent(pdata->dev,
					(sizeof(struct xlgmac_dma_desc) *
					 dma_desc_count),
					&ring->dma_desc_head_addr,
					GFP_KERNEL);
	if (!ring->dma_desc_head)
		return -ENOMEM;

	/* Array of descriptor data */
	ring->desc_data_head = kcalloc(dma_desc_count,
					sizeof(struct xlgmac_desc_data),
					GFP_KERNEL);
	if (!ring->desc_data_head)
		return -ENOMEM;

	netif_dbg(pdata, drv, pdata->netdev,
		  "dma_desc_head=%p, dma_desc_head_addr=%pad, desc_data_head=%p\n",
		ring->dma_desc_head,
		&ring->dma_desc_head_addr,
		ring->desc_data_head);

	return 0;
}