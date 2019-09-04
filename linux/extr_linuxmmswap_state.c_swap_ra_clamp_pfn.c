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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFN_DOWN (unsigned long) ; 
 unsigned long PMD_MASK ; 
 unsigned long PMD_SIZE ; 
 unsigned long max3 (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long min3 (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void swap_ra_clamp_pfn(struct vm_area_struct *vma,
				     unsigned long faddr,
				     unsigned long lpfn,
				     unsigned long rpfn,
				     unsigned long *start,
				     unsigned long *end)
{
	*start = max3(lpfn, PFN_DOWN(vma->vm_start),
		      PFN_DOWN(faddr & PMD_MASK));
	*end = min3(rpfn, PFN_DOWN(vma->vm_end),
		    PFN_DOWN((faddr & PMD_MASK) + PMD_SIZE));
}