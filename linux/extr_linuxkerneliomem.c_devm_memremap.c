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
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 int /*<<< orphan*/  devm_memremap_release ; 
 int /*<<< orphan*/  devres_add (struct device*,void**) ; 
 void** devres_alloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (void**) ; 
 void* memremap (int /*<<< orphan*/ ,size_t,unsigned long) ; 

void *devm_memremap(struct device *dev, resource_size_t offset,
		size_t size, unsigned long flags)
{
	void **ptr, *addr;

	ptr = devres_alloc_node(devm_memremap_release, sizeof(*ptr), GFP_KERNEL,
			dev_to_node(dev));
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	addr = memremap(offset, size, flags);
	if (addr) {
		*ptr = addr;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
		return ERR_PTR(-ENXIO);
	}

	return addr;
}