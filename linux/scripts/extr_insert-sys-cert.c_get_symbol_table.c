#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int e_shoff; unsigned int e_shnum; } ;
struct TYPE_5__ {unsigned int sh_size; scalar_t__ sh_type; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 unsigned int SHN_UNDEF ; 
 scalar_t__ SHT_SYMTAB ; 

__attribute__((used)) static Elf_Shdr *get_symbol_table(Elf_Ehdr *hdr)
{
	Elf_Shdr *x;
	unsigned int i, num_sections;

	x = (void *)hdr + hdr->e_shoff;
	if (hdr->e_shnum == SHN_UNDEF)
		num_sections = x[0].sh_size;
	else
		num_sections = hdr->e_shnum;

	for (i = 1; i < num_sections; i++)
		if (x[i].sh_type == SHT_SYMTAB)
			return &x[i];
	return NULL;
}