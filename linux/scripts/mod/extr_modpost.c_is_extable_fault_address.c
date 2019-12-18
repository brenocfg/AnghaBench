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
 int /*<<< orphan*/  fatal (char*) ; 

__attribute__((used)) static inline bool is_extable_fault_address(Elf_Rela *r)
{
	/*
	 * extable_entry_size is only discovered after we've handled the
	 * _second_ relocation in __ex_table, so only abort when we're not
	 * handling the first reloc and extable_entry_size is zero.
	 */
	if (r->r_offset && extable_entry_size == 0)
		fatal("extable_entry size hasn't been discovered!\n");

	return ((r->r_offset == 0) ||
		(r->r_offset % extable_entry_size == 0));
}