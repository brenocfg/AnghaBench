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
struct elf_info {TYPE_1__* hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_type; } ;
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  TYPE_2__ Elf_Rela ;

/* Variables and functions */
 unsigned int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_EXEC ; 
#define  R_386_32 129 
#define  R_386_PC32 128 
 int /*<<< orphan*/  TO_NATIVE (unsigned int) ; 
 unsigned int* reloc_location (struct elf_info*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int addend_386_rel(struct elf_info *elf, Elf_Shdr *sechdr, Elf_Rela *r)
{
	unsigned int r_typ = ELF_R_TYPE(r->r_info);
	unsigned int *location = reloc_location(elf, sechdr, r);

	switch (r_typ) {
	case R_386_32:
		r->r_addend = TO_NATIVE(*location);
		break;
	case R_386_PC32:
		r->r_addend = TO_NATIVE(*location) + 4;
		/* For CONFIG_RELOCATABLE=y */
		if (elf->hdr->e_type == ET_EXEC)
			r->r_addend += r->r_offset;
		break;
	}
	return 0;
}