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
struct vm_area_struct {scalar_t__ anon_vma; TYPE_1__* vm_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  anon_vma_lock_write (scalar_t__) ; 
 int /*<<< orphan*/  i_mmap_lock_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void take_rmap_locks(struct vm_area_struct *vma)
{
	if (vma->vm_file)
		i_mmap_lock_write(vma->vm_file->f_mapping);
	if (vma->anon_vma)
		anon_vma_lock_write(vma->anon_vma);
}