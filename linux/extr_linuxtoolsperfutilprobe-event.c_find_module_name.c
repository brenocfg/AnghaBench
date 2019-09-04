#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ d_buf; } ;
struct TYPE_6__ {scalar_t__* e_ident; } ;
typedef  int /*<<< orphan*/  GElf_Shdr ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_2__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS32 ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PERF_ELF_C_READ_MMAP ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 TYPE_2__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_section_by_name (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *find_module_name(const char *module)
{
	int fd;
	Elf *elf;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	Elf_Data *data;
	Elf_Scn *sec;
	char *mod_name = NULL;
	int name_offset;

	fd = open(module, O_RDONLY);
	if (fd < 0)
		return NULL;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, NULL);
	if (elf == NULL)
		goto elf_err;

	if (gelf_getehdr(elf, &ehdr) == NULL)
		goto ret_err;

	sec = elf_section_by_name(elf, &ehdr, &shdr,
			".gnu.linkonce.this_module", NULL);
	if (!sec)
		goto ret_err;

	data = elf_getdata(sec, NULL);
	if (!data || !data->d_buf)
		goto ret_err;

	/*
	 * NOTE:
	 * '.gnu.linkonce.this_module' section of kernel module elf directly
	 * maps to 'struct module' from linux/module.h. This section contains
	 * actual module name which will be used by kernel after loading it.
	 * But, we cannot use 'struct module' here since linux/module.h is not
	 * exposed to user-space. Offset of 'name' has remained same from long
	 * time, so hardcoding it here.
	 */
	if (ehdr.e_ident[EI_CLASS] == ELFCLASS32)
		name_offset = 12;
	else	/* expect ELFCLASS64 by default */
		name_offset = 24;

	mod_name = strdup((char *)data->d_buf + name_offset);

ret_err:
	elf_end(elf);
elf_err:
	close(fd);
	return mod_name;
}