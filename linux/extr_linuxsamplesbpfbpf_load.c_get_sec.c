#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  e_shstrndx; } ;
struct TYPE_7__ {int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ *,int) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int get_sec(Elf *elf, int i, GElf_Ehdr *ehdr, char **shname,
		   GElf_Shdr *shdr, Elf_Data **data)
{
	Elf_Scn *scn;

	scn = elf_getscn(elf, i);
	if (!scn)
		return 1;

	if (gelf_getshdr(scn, shdr) != shdr)
		return 2;

	*shname = elf_strptr(elf, ehdr->e_shstrndx, shdr->sh_name);
	if (!*shname || !shdr->sh_size)
		return 3;

	*data = elf_getdata(scn, 0);
	if (!*data || elf_getdata(scn, *data) != NULL)
		return 4;

	return 0;
}