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
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_area_cachep ; 

void vm_area_free(struct vm_area_struct *vma)
{
	kmem_cache_free(vm_area_cachep, vma);
}