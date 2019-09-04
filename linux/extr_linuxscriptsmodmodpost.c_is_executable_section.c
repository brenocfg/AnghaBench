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
struct elf_info {unsigned int num_sections; TYPE_1__* sechdrs; } ;
struct TYPE_2__ {int sh_flags; } ;

/* Variables and functions */
 int SHF_EXECINSTR ; 
 int /*<<< orphan*/  fatal (char*) ; 

__attribute__((used)) static int is_executable_section(struct elf_info* elf, unsigned int section_index)
{
	if (section_index > elf->num_sections)
		fatal("section_index is outside elf->num_sections!\n");

	return ((elf->sechdrs[section_index].sh_flags & SHF_EXECINSTR) == SHF_EXECINSTR);
}