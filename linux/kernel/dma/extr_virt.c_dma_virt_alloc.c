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
struct device {int dummy; } ;
typedef  int gfp_t ;
typedef  uintptr_t dma_addr_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 

__attribute__((used)) static void *dma_virt_alloc(struct device *dev, size_t size,
			    dma_addr_t *dma_handle, gfp_t gfp,
			    unsigned long attrs)
{
	void *ret;

	ret = (void *)__get_free_pages(gfp | __GFP_ZERO, get_order(size));
	if (ret)
		*dma_handle = (uintptr_t)ret;
	return ret;
}