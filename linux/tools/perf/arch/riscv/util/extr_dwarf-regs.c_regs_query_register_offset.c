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
struct pt_regs_dwarfnum {int dwarfnum; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pt_regs_dwarfnum* riscv_dwarf_regs_table ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

int regs_query_register_offset(const char *name)
{
	const struct pt_regs_dwarfnum *roff;

	for (roff = riscv_dwarf_regs_table; roff->name; roff++)
		if (!strcmp(roff->name, name))
			return roff->dwarfnum;
	return -EINVAL;
}