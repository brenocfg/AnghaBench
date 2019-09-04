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

/* Variables and functions */
 int /*<<< orphan*/  vunmap (void const*) ; 

__attribute__((used)) static inline void erofs_vunmap(const void *mem, unsigned int count)
{
#ifdef CONFIG_EROFS_FS_USE_VM_MAP_RAM
	vm_unmap_ram(mem, count);
#else
	vunmap(mem);
#endif
}