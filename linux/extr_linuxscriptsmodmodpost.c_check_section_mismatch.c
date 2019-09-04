#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sectioncheck {int /*<<< orphan*/  (* handler ) (char const*,struct elf_info*,struct sectioncheck const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ;} ;
struct elf_info {int dummy; } ;
typedef  int /*<<< orphan*/  Elf_Sym ;
typedef  int /*<<< orphan*/  Elf_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  default_mismatch_handler (char const*,struct elf_info*,struct sectioncheck const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  get_secindex (struct elf_info*,int /*<<< orphan*/ *) ; 
 char* sec_name (struct elf_info*,int /*<<< orphan*/ ) ; 
 struct sectioncheck* section_mismatch (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (char const*,struct elf_info*,struct sectioncheck const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void check_section_mismatch(const char *modname, struct elf_info *elf,
				   Elf_Rela *r, Elf_Sym *sym, const char *fromsec)
{
	const char *tosec = sec_name(elf, get_secindex(elf, sym));
	const struct sectioncheck *mismatch = section_mismatch(fromsec, tosec);

	if (mismatch) {
		if (mismatch->handler)
			mismatch->handler(modname, elf,  mismatch,
					  r, sym, fromsec);
		else
			default_mismatch_handler(modname, elf, mismatch,
						 r, sym, fromsec);
	}
}