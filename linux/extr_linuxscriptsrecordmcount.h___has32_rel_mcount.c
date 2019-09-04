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
struct TYPE_4__ {int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_name; int /*<<< orphan*/  sh_info; } ;
typedef  TYPE_1__ Elf_Shdr ;

/* Variables and functions */
 int SHF_EXECINSTR ; 
 size_t SHT_PROGBITS ; 
 int _w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const* const) ; 
 int /*<<< orphan*/  succeed_file () ; 
 size_t w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char const *
__has_rel_mcount(Elf_Shdr const *const relhdr,  /* is SHT_REL or SHT_RELA */
		 Elf_Shdr const *const shdr0,
		 char const *const shstrtab,
		 char const *const fname)
{
	/* .sh_info depends on .sh_type == SHT_REL[,A] */
	Elf_Shdr const *const txthdr = &shdr0[w(relhdr->sh_info)];
	char const *const txtname = &shstrtab[w(txthdr->sh_name)];

	if (strcmp("__mcount_loc", txtname) == 0) {
		fprintf(stderr, "warning: __mcount_loc already exists: %s\n",
			fname);
		succeed_file();
	}
	if (w(txthdr->sh_type) != SHT_PROGBITS ||
	    !(_w(txthdr->sh_flags) & SHF_EXECINSTR))
		return NULL;
	return txtname;
}