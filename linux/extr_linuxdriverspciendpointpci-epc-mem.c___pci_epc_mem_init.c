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
struct pci_epc_mem {unsigned long* bitmap; size_t page_size; int pages; size_t size; int /*<<< orphan*/  phys_base; } ;
struct pci_epc {struct pci_epc_mem* mem; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 unsigned int ilog2 (size_t) ; 
 int /*<<< orphan*/  kfree (struct pci_epc_mem*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

int __pci_epc_mem_init(struct pci_epc *epc, phys_addr_t phys_base, size_t size,
		       size_t page_size)
{
	int ret;
	struct pci_epc_mem *mem;
	unsigned long *bitmap;
	unsigned int page_shift;
	int pages;
	int bitmap_size;

	if (page_size < PAGE_SIZE)
		page_size = PAGE_SIZE;

	page_shift = ilog2(page_size);
	pages = size >> page_shift;
	bitmap_size = BITS_TO_LONGS(pages) * sizeof(long);

	mem = kzalloc(sizeof(*mem), GFP_KERNEL);
	if (!mem) {
		ret = -ENOMEM;
		goto err;
	}

	bitmap = kzalloc(bitmap_size, GFP_KERNEL);
	if (!bitmap) {
		ret = -ENOMEM;
		goto err_mem;
	}

	mem->bitmap = bitmap;
	mem->phys_base = phys_base;
	mem->page_size = page_size;
	mem->pages = pages;
	mem->size = size;

	epc->mem = mem;

	return 0;

err_mem:
	kfree(mem);

err:
return ret;
}