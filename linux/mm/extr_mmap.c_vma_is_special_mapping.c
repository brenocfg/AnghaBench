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
struct vm_special_mapping {int dummy; } ;
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; struct vm_special_mapping const* vm_private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  legacy_special_mapping_vmops ; 
 int /*<<< orphan*/  special_mapping_vmops ; 

bool vma_is_special_mapping(const struct vm_area_struct *vma,
	const struct vm_special_mapping *sm)
{
	return vma->vm_private_data == sm &&
		(vma->vm_ops == &special_mapping_vmops ||
		 vma->vm_ops == &legacy_special_mapping_vmops);
}