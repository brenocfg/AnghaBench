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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __vm_insert_mixed (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int) ; 

vm_fault_t vmf_insert_mixed(struct vm_area_struct *vma, unsigned long addr,
		pfn_t pfn)
{
	return __vm_insert_mixed(vma, addr, pfn, false);
}