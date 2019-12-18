#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdp_umem {unsigned int npgs; TYPE_1__* pages; int /*<<< orphan*/ * pgs; } ;
struct TYPE_2__ {void* addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 scalar_t__ PageHighMem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 void* vmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_umem_unmap_pages (struct xdp_umem*) ; 

__attribute__((used)) static int xdp_umem_map_pages(struct xdp_umem *umem)
{
	unsigned int i;
	void *addr;

	for (i = 0; i < umem->npgs; i++) {
		if (PageHighMem(umem->pgs[i]))
			addr = vmap(&umem->pgs[i], 1, VM_MAP, PAGE_KERNEL);
		else
			addr = page_address(umem->pgs[i]);

		if (!addr) {
			xdp_umem_unmap_pages(umem);
			return -ENOMEM;
		}

		umem->pages[i].addr = addr;
	}

	return 0;
}