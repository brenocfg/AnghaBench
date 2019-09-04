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
struct TYPE_4__ {size_t e_phnum; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 TYPE_1__* gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int elf_getphdrnum(Elf *elf, size_t *dst)
{
	GElf_Ehdr gehdr;
	GElf_Ehdr *ehdr;

	ehdr = gelf_getehdr(elf, &gehdr);
	if (!ehdr)
		return -1;

	*dst = ehdr->e_phnum;

	return 0;
}