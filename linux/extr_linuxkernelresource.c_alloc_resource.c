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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct resource* bootmem_resource_free ; 
 int /*<<< orphan*/  bootmem_resource_lock ; 
 struct resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct resource *alloc_resource(gfp_t flags)
{
	struct resource *res = NULL;

	spin_lock(&bootmem_resource_lock);
	if (bootmem_resource_free) {
		res = bootmem_resource_free;
		bootmem_resource_free = res->sibling;
	}
	spin_unlock(&bootmem_resource_lock);

	if (res)
		memset(res, 0, sizeof(struct resource));
	else
		res = kzalloc(sizeof(struct resource), flags);

	return res;
}