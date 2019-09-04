#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sh_type; } ;
typedef  TYPE_1__ Elf_Shdr ;

/* Variables and functions */
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 char const* __has_rel_mcount (TYPE_1__ const* const,TYPE_1__ const* const,char const* const,char const* const) ; 
 scalar_t__ w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char const *has_rel_mcount(Elf_Shdr const *const relhdr,
				  Elf_Shdr const *const shdr0,
				  char const *const shstrtab,
				  char const *const fname)
{
	if (w(relhdr->sh_type) != SHT_REL && w(relhdr->sh_type) != SHT_RELA)
		return NULL;
	return __has_rel_mcount(relhdr, shdr0, shstrtab, fname);
}