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
struct elf_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ sh_type; int sh_flags; } ;
typedef  TYPE_1__ Elf_Shdr ;

/* Variables and functions */
 int SHF_ALLOC ; 
 scalar_t__ SHT_PROGBITS ; 
 int /*<<< orphan*/  match (char const*,int /*<<< orphan*/ ) ; 
 char* sech_name (struct elf_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  section_white_list ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*) ; 

__attribute__((used)) static void check_section(const char *modname, struct elf_info *elf,
			  Elf_Shdr *sechdr)
{
	const char *sec = sech_name(elf, sechdr);

	if (sechdr->sh_type == SHT_PROGBITS &&
	    !(sechdr->sh_flags & SHF_ALLOC) &&
	    !match(sec, section_white_list)) {
		warn("%s (%s): unexpected non-allocatable section.\n"
		     "Did you forget to use \"ax\"/\"aw\" in a .S file?\n"
		     "Note that for example <linux/init.h> contains\n"
		     "section definitions for use in .S files.\n\n",
		     modname, sec);
	}
}