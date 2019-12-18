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
struct TYPE_3__ {scalar_t__ e_type; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ ET_EXEC ; 
 int /*<<< orphan*/  PERF_ELF_C_READ_MMAP ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int) ; 

__attribute__((used)) static int elf_is_exec(int fd, const char *name)
{
	Elf *elf;
	GElf_Ehdr ehdr;
	int retval = 0;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, NULL);
	if (elf == NULL)
		return 0;
	if (gelf_getehdr(elf, &ehdr) == NULL)
		goto out;

	retval = (ehdr.e_type == ET_EXEC);

out:
	elf_end(elf);
	pr_debug("unwind: elf_is_exec(%s): %d\n", name, retval);
	return retval;
}