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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fake_ptr_to_pci (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *fake_alloc_consistent(struct device *parent, size_t size,
		dma_addr_t *dma)
{
	void *alloc = kmalloc(size, GFP_KERNEL);

	if (alloc)
		*dma = fake_ptr_to_pci(alloc);

	return alloc;
}