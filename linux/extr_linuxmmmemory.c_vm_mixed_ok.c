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
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int VM_MIXEDMAP ; 
 scalar_t__ is_zero_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_t_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_t_special (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_t_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vm_mixed_ok(struct vm_area_struct *vma, pfn_t pfn)
{
	/* these checks mirror the abort conditions in vm_normal_page */
	if (vma->vm_flags & VM_MIXEDMAP)
		return true;
	if (pfn_t_devmap(pfn))
		return true;
	if (pfn_t_special(pfn))
		return true;
	if (is_zero_pfn(pfn_t_to_pfn(pfn)))
		return true;
	return false;
}