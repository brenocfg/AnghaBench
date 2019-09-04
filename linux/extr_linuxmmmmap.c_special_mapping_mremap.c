#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_special_mapping {int (* mremap ) (struct vm_special_mapping*,struct vm_area_struct*) ;} ;
struct vm_area_struct {scalar_t__ vm_mm; struct vm_special_mapping* vm_private_data; } ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 TYPE_1__* current ; 
 int stub1 (struct vm_special_mapping*,struct vm_area_struct*) ; 

__attribute__((used)) static int special_mapping_mremap(struct vm_area_struct *new_vma)
{
	struct vm_special_mapping *sm = new_vma->vm_private_data;

	if (WARN_ON_ONCE(current->mm != new_vma->vm_mm))
		return -EFAULT;

	if (sm->mremap)
		return sm->mremap(sm, new_vma);

	return 0;
}