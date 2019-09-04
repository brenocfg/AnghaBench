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
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_page (void*) ; 

int dma_common_get_sgtable(struct device *dev, struct sg_table *sgt,
		 void *cpu_addr, dma_addr_t handle, size_t size)
{
	struct page *page = virt_to_page(cpu_addr);
	int ret;

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	if (unlikely(ret))
		return ret;

	sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	return 0;
}