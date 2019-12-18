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
struct resource {struct resource* sibling; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageSlab (int /*<<< orphan*/ ) ; 
 struct resource* bootmem_resource_free ; 
 int /*<<< orphan*/  bootmem_resource_lock ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_head_page (struct resource*) ; 

__attribute__((used)) static void free_resource(struct resource *res)
{
	if (!res)
		return;

	if (!PageSlab(virt_to_head_page(res))) {
		spin_lock(&bootmem_resource_lock);
		res->sibling = bootmem_resource_free;
		bootmem_resource_free = res;
		spin_unlock(&bootmem_resource_lock);
	} else {
		kfree(res);
	}
}