#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct debuginfo {int /*<<< orphan*/  mod; int /*<<< orphan*/  bias; } ;
struct TYPE_4__ {scalar_t__ sh_offset; int /*<<< orphan*/  sh_addr; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf32_Word ;
typedef  int /*<<< orphan*/  Elf ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/ * dwfl_module_getelf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* dwfl_module_relocation_info (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int dwfl_module_relocations (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int debuginfo__get_text_offset(struct debuginfo *dbg, Dwarf_Addr *offs,
				bool adjust_offset)
{
	int n, i;
	Elf32_Word shndx;
	Elf_Scn *scn;
	Elf *elf;
	GElf_Shdr mem, *shdr;
	const char *p;

	elf = dwfl_module_getelf(dbg->mod, &dbg->bias);
	if (!elf)
		return -EINVAL;

	/* Get the number of relocations */
	n = dwfl_module_relocations(dbg->mod);
	if (n < 0)
		return -ENOENT;
	/* Search the relocation related .text section */
	for (i = 0; i < n; i++) {
		p = dwfl_module_relocation_info(dbg->mod, i, &shndx);
		if (strcmp(p, ".text") == 0) {
			/* OK, get the section header */
			scn = elf_getscn(elf, shndx);
			if (!scn)
				return -ENOENT;
			shdr = gelf_getshdr(scn, &mem);
			if (!shdr)
				return -ENOENT;
			*offs = shdr->sh_addr;
			if (adjust_offset)
				*offs -= shdr->sh_offset;
		}
	}
	return 0;
}