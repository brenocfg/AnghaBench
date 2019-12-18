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
typedef  int u64 ;
struct resource {int start; int end; int flags; struct resource* child; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IO_STRICT_DEVMEM ; 
 int IORESOURCE_BUSY ; 
 int IORESOURCE_EXCLUSIVE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 struct resource iomem_resource ; 
 struct resource* r_next (int /*<<< orphan*/ *,struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_lock ; 
 int /*<<< orphan*/  strict_iomem_checks ; 

bool iomem_is_exclusive(u64 addr)
{
	struct resource *p = &iomem_resource;
	bool err = false;
	loff_t l;
	int size = PAGE_SIZE;

	if (!strict_iomem_checks)
		return false;

	addr = addr & PAGE_MASK;

	read_lock(&resource_lock);
	for (p = p->child; p ; p = r_next(NULL, p, &l)) {
		/*
		 * We can probably skip the resources without
		 * IORESOURCE_IO attribute?
		 */
		if (p->start >= addr + size)
			break;
		if (p->end < addr)
			continue;
		/*
		 * A resource is exclusive if IORESOURCE_EXCLUSIVE is set
		 * or CONFIG_IO_STRICT_DEVMEM is enabled and the
		 * resource is busy.
		 */
		if ((p->flags & IORESOURCE_BUSY) == 0)
			continue;
		if (IS_ENABLED(CONFIG_IO_STRICT_DEVMEM)
				|| p->flags & IORESOURCE_EXCLUSIVE) {
			err = true;
			break;
		}
	}
	read_unlock(&resource_lock);

	return err;
}