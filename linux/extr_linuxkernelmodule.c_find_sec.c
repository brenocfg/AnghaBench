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
struct load_info {scalar_t__ secstrings; TYPE_2__* sechdrs; TYPE_1__* hdr; } ;
struct TYPE_4__ {int sh_flags; scalar_t__ sh_name; } ;
struct TYPE_3__ {unsigned int e_shnum; } ;
typedef  TYPE_2__ Elf_Shdr ;

/* Variables and functions */
 int SHF_ALLOC ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static unsigned int find_sec(const struct load_info *info, const char *name)
{
	unsigned int i;

	for (i = 1; i < info->hdr->e_shnum; i++) {
		Elf_Shdr *shdr = &info->sechdrs[i];
		/* Alloc bit cleared means "ignore it." */
		if ((shdr->sh_flags & SHF_ALLOC)
		    && strcmp(info->secstrings + shdr->sh_name, name) == 0)
			return i;
	}
	return 0;
}