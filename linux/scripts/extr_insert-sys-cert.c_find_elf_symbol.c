#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int e_shoff; } ;
struct TYPE_8__ {unsigned int sh_link; int sh_offset; int sh_size; int sh_entsize; } ;
struct TYPE_7__ {int st_name; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  TYPE_3__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static Elf_Sym *find_elf_symbol(Elf_Ehdr *hdr, Elf_Shdr *symtab, char *name)
{
	Elf_Sym *sym, *symtab_start;
	char *strtab, *symname;
	unsigned int link;
	Elf_Shdr *x;
	int i, n;

	x = (void *)hdr + hdr->e_shoff;
	link = symtab->sh_link;
	symtab_start = (void *)hdr + symtab->sh_offset;
	n = symtab->sh_size / symtab->sh_entsize;
	strtab = (void *)hdr + x[link].sh_offset;

	for (i = 0; i < n; i++) {
		sym = &symtab_start[i];
		symname = strtab + sym->st_name;
		if (strcmp(symname, name) == 0)
			return sym;
	}
	err("Unable to find symbol: %s\n", name);
	return NULL;
}