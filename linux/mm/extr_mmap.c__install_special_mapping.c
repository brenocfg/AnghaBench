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
struct vm_area_struct {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 struct vm_area_struct* __install_special_mapping (struct mm_struct*,unsigned long,unsigned long,unsigned long,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  special_mapping_vmops ; 

struct vm_area_struct *_install_special_mapping(
	struct mm_struct *mm,
	unsigned long addr, unsigned long len,
	unsigned long vm_flags, const struct vm_special_mapping *spec)
{
	return __install_special_mapping(mm, addr, len, vm_flags, (void *)spec,
					&special_mapping_vmops);
}