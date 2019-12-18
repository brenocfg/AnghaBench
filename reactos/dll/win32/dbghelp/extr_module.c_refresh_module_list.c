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
struct process {int dummy; } ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ elf_synchronize_module_list (struct process*) ; 
 scalar_t__ macho_synchronize_module_list (struct process*) ; 

__attribute__((used)) static BOOL refresh_module_list(struct process* pcs)
{
    /* force transparent ELF and Mach-O loading / unloading */
    return elf_synchronize_module_list(pcs) || macho_synchronize_module_list(pcs);
}