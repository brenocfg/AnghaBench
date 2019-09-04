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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* vm_map_ram (struct page**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_unmap_ram (void*,int) ; 

__attribute__((used)) static int ion_heap_clear_pages(struct page **pages, int num, pgprot_t pgprot)
{
	void *addr = vm_map_ram(pages, num, -1, pgprot);

	if (!addr)
		return -ENOMEM;
	memset(addr, 0, PAGE_SIZE * num);
	vm_unmap_ram(addr, num);

	return 0;
}