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
struct vm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 struct vm_struct* __get_vm_area_node (unsigned long,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

struct vm_struct *get_vm_area_caller(unsigned long size, unsigned long flags,
				const void *caller)
{
	return __get_vm_area_node(size, 1, flags, VMALLOC_START, VMALLOC_END,
				  NUMA_NO_NODE, GFP_KERNEL, caller);
}