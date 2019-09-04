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
struct vm_area_struct {int vm_flags; } ;
struct iomap {int flags; } ;

/* Variables and functions */
 int IOMAP_F_DIRTY ; 
 unsigned long IOMAP_WRITE ; 
 int VM_SYNC ; 

__attribute__((used)) static bool dax_fault_is_synchronous(unsigned long flags,
		struct vm_area_struct *vma, struct iomap *iomap)
{
	return (flags & IOMAP_WRITE) && (vma->vm_flags & VM_SYNC)
		&& (iomap->flags & IOMAP_F_DIRTY);
}