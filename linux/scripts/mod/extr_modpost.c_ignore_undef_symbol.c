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
struct elf_info {TYPE_1__* hdr; } ;
struct TYPE_2__ {scalar_t__ e_machine; } ;

/* Variables and functions */
 scalar_t__ EM_PPC ; 
 scalar_t__ EM_PPC64 ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 

__attribute__((used)) static int ignore_undef_symbol(struct elf_info *info, const char *symname)
{
	/* ignore __this_module, it will be resolved shortly */
	if (strcmp(symname, "__this_module") == 0)
		return 1;
	/* ignore global offset table */
	if (strcmp(symname, "_GLOBAL_OFFSET_TABLE_") == 0)
		return 1;
	if (info->hdr->e_machine == EM_PPC)
		/* Special register function linked on all modules during final link of .ko */
		if (strstarts(symname, "_restgpr_") ||
		    strstarts(symname, "_savegpr_") ||
		    strstarts(symname, "_rest32gpr_") ||
		    strstarts(symname, "_save32gpr_") ||
		    strstarts(symname, "_restvr_") ||
		    strstarts(symname, "_savevr_"))
			return 1;
	if (info->hdr->e_machine == EM_PPC64)
		/* Special register function linked on all modules during final link of .ko */
		if (strstarts(symname, "_restgpr0_") ||
		    strstarts(symname, "_savegpr0_") ||
		    strstarts(symname, "_restvr_") ||
		    strstarts(symname, "_savevr_") ||
		    strcmp(symname, ".TOC.") == 0)
			return 1;
	/* Do not ignore this symbol */
	return 0;
}