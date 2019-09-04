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
struct nvme_dev {void* prp_page_pool; void* prp_small_pool; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (void*) ; 

__attribute__((used)) static int nvme_setup_prp_pools(struct nvme_dev *dev)
{
	dev->prp_page_pool = dma_pool_create("prp list page", dev->dev,
						PAGE_SIZE, PAGE_SIZE, 0);
	if (!dev->prp_page_pool)
		return -ENOMEM;

	/* Optimisation for I/Os between 4k and 128k */
	dev->prp_small_pool = dma_pool_create("prp list 256", dev->dev,
						256, 256, 0);
	if (!dev->prp_small_pool) {
		dma_pool_destroy(dev->prp_page_pool);
		return -ENOMEM;
	}
	return 0;
}