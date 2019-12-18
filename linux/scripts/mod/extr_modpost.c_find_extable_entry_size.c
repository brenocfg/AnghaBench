#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int r_offset; } ;
typedef  TYPE_1__ Elf_Rela ;

/* Variables and functions */
 int extable_entry_size ; 

__attribute__((used)) static void find_extable_entry_size(const char* const sec, const Elf_Rela* r)
{
	/*
	 * If we're currently checking the second relocation within __ex_table,
	 * that relocation offset tells us the offsetof(struct
	 * exception_table_entry, fixup) which is equal to sizeof(struct
	 * exception_table_entry) divided by two.  We use that to our advantage
	 * since there's no portable way to get that size as every architecture
	 * seems to go with different sized types.  Not pretty but better than
	 * hard-coding the size for every architecture..
	 */
	if (!extable_entry_size)
		extable_entry_size = r->r_offset * 2;
}