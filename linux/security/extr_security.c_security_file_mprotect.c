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
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  file_mprotect ; 

int security_file_mprotect(struct vm_area_struct *vma, unsigned long reqprot,
			    unsigned long prot)
{
	return call_int_hook(file_mprotect, 0, vma, reqprot, prot);
}