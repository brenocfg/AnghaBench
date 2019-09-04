#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int e_phnum; } ;
struct TYPE_3__ {scalar_t__ p_type; int p_offset; int /*<<< orphan*/  p_filesz; } ;
typedef  TYPE_1__ Elf64_Phdr ;
typedef  TYPE_2__ Elf64_Ehdr ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 scalar_t__ PT_NOTE ; 
 int stack_map_parse_build_id (void*,unsigned char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stack_map_get_build_id_64(void *page_addr,
				     unsigned char *build_id)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)page_addr;
	Elf64_Phdr *phdr;
	int i;

	/* only supports phdr that fits in one page */
	if (ehdr->e_phnum >
	    (PAGE_SIZE - sizeof(Elf64_Ehdr)) / sizeof(Elf64_Phdr))
		return -EINVAL;

	phdr = (Elf64_Phdr *)(page_addr + sizeof(Elf64_Ehdr));

	for (i = 0; i < ehdr->e_phnum; ++i)
		if (phdr[i].p_type == PT_NOTE)
			return stack_map_parse_build_id(page_addr, build_id,
					page_addr + phdr[i].p_offset,
					phdr[i].p_filesz);
	return -EINVAL;
}