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
struct pci_dev {int dummy; } ;
struct ct_vm_block {int size; int /*<<< orphan*/  list; scalar_t__ addr; } ;
struct ct_vm {int size; int /*<<< orphan*/  unused; int /*<<< orphan*/  used; int /*<<< orphan*/  get_ptp_phys; int /*<<< orphan*/  unmap; int /*<<< orphan*/  map; int /*<<< orphan*/ * ptp; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CT_ADDRS_PER_PAGE ; 
 int CT_PTP_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  ct_get_ptp_phys ; 
 int /*<<< orphan*/  ct_vm_destroy (struct ct_vm*) ; 
 int /*<<< orphan*/  ct_vm_map ; 
 int /*<<< orphan*/  ct_vm_unmap ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_pci_data (struct pci_dev*) ; 

int ct_vm_create(struct ct_vm **rvm, struct pci_dev *pci)
{
	struct ct_vm *vm;
	struct ct_vm_block *block;
	int i, err = 0;

	*rvm = NULL;

	vm = kzalloc(sizeof(*vm), GFP_KERNEL);
	if (!vm)
		return -ENOMEM;

	mutex_init(&vm->lock);

	/* Allocate page table pages */
	for (i = 0; i < CT_PTP_NUM; i++) {
		err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
					  snd_dma_pci_data(pci),
					  PAGE_SIZE, &vm->ptp[i]);
		if (err < 0)
			break;
	}
	if (err < 0) {
		/* no page table pages are allocated */
		ct_vm_destroy(vm);
		return -ENOMEM;
	}
	vm->size = CT_ADDRS_PER_PAGE * i;
	vm->map = ct_vm_map;
	vm->unmap = ct_vm_unmap;
	vm->get_ptp_phys = ct_get_ptp_phys;
	INIT_LIST_HEAD(&vm->unused);
	INIT_LIST_HEAD(&vm->used);
	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (NULL != block) {
		block->addr = 0;
		block->size = vm->size;
		list_add(&block->list, &vm->unused);
	}

	*rvm = vm;
	return 0;
}