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
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sba_map_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *sba_alloc(struct device *hwdev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	void *ret;

	if (!hwdev) {
		/* only support PCI */
		*dma_handle = 0;
		return NULL;
	}

        ret = (void *) __get_free_pages(gfp, get_order(size));

	if (ret) {
		memset(ret, 0, size);
		*dma_handle = sba_map_single(hwdev, ret, size, 0);
	}

	return ret;
}