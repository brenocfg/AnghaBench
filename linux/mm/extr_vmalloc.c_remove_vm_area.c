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
struct vmap_area {struct vm_struct* vm; } ;
struct vm_struct {int dummy; } ;

/* Variables and functions */
 struct vmap_area* __find_vmap_area (unsigned long) ; 
 int /*<<< orphan*/  free_unmap_vmap_area (struct vmap_area*) ; 
 int /*<<< orphan*/  kasan_free_shadow (struct vm_struct*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmap_area_lock ; 

struct vm_struct *remove_vm_area(const void *addr)
{
	struct vmap_area *va;

	might_sleep();

	spin_lock(&vmap_area_lock);
	va = __find_vmap_area((unsigned long)addr);
	if (va && va->vm) {
		struct vm_struct *vm = va->vm;

		va->vm = NULL;
		spin_unlock(&vmap_area_lock);

		kasan_free_shadow(vm);
		free_unmap_vmap_area(va);

		return vm;
	}

	spin_unlock(&vmap_area_lock);
	return NULL;
}