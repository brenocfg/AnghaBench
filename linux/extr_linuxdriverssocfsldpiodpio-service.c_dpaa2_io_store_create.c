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
struct dpaa2_io_store {unsigned int max; struct device* dev; scalar_t__ idx; struct dpaa2_io_store* alloced_addr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct dpaa2_dq {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PTR_ALIGN (struct dpaa2_io_store*,int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dpaa2_io_store*) ; 
 struct dpaa2_io_store* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dpaa2_io_store* kzalloc (size_t,int /*<<< orphan*/ ) ; 

struct dpaa2_io_store *dpaa2_io_store_create(unsigned int max_frames,
					     struct device *dev)
{
	struct dpaa2_io_store *ret;
	size_t size;

	if (!max_frames || (max_frames > 16))
		return NULL;

	ret = kmalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return NULL;

	ret->max = max_frames;
	size = max_frames * sizeof(struct dpaa2_dq) + 64;
	ret->alloced_addr = kzalloc(size, GFP_KERNEL);
	if (!ret->alloced_addr) {
		kfree(ret);
		return NULL;
	}

	ret->vaddr = PTR_ALIGN(ret->alloced_addr, 64);
	ret->paddr = dma_map_single(dev, ret->vaddr,
				    sizeof(struct dpaa2_dq) * max_frames,
				    DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, ret->paddr)) {
		kfree(ret->alloced_addr);
		kfree(ret);
		return NULL;
	}

	ret->idx = 0;
	ret->dev = dev;

	return ret;
}