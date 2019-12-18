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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long VM_EXEC ; 
 unsigned long VM_READ ; 
 unsigned long VM_SHARED ; 
 unsigned long VM_WRITE ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int /*<<< orphan*/  arch_filter_pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_vm_get_page_prot (unsigned long) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * protection_map ; 

pgprot_t vm_get_page_prot(unsigned long vm_flags)
{
	pgprot_t ret = __pgprot(pgprot_val(protection_map[vm_flags &
				(VM_READ|VM_WRITE|VM_EXEC|VM_SHARED)]) |
			pgprot_val(arch_vm_get_page_prot(vm_flags)));

	return arch_filter_pgprot(ret);
}