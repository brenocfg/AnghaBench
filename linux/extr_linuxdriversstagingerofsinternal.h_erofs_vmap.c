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

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 void* vmap (struct page**,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *erofs_vmap(struct page **pages, unsigned int count)
{
#ifdef CONFIG_EROFS_FS_USE_VM_MAP_RAM
	int i = 0;

	while (1) {
		void *addr = vm_map_ram(pages, count, -1, PAGE_KERNEL);
		/* retry two more times (totally 3 times) */
		if (addr != NULL || ++i >= 3)
			return addr;
		vm_unmap_aliases();
	}
	return NULL;
#else
	return vmap(pages, count, VM_MAP, PAGE_KERNEL);
#endif
}