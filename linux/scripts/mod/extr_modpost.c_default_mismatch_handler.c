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
struct sectioncheck {int dummy; } ;
struct elf_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_addend; } ;
typedef  int /*<<< orphan*/  Elf_Sym ;
typedef  TYPE_1__ Elf_Rela ;

/* Variables and functions */
 int /*<<< orphan*/ * find_elf_symbol (struct elf_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_elf_symbol2 (struct elf_info*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_secindex (struct elf_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_sec_mismatch (char const*,struct sectioncheck const* const,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 char* sec_name (struct elf_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ secref_whitelist (struct sectioncheck const* const,char const*,char const*,char const*,char const*) ; 
 scalar_t__ strstarts (char const*,char*) ; 
 char* sym_name (struct elf_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void default_mismatch_handler(const char *modname, struct elf_info *elf,
				     const struct sectioncheck* const mismatch,
				     Elf_Rela *r, Elf_Sym *sym, const char *fromsec)
{
	const char *tosec;
	Elf_Sym *to;
	Elf_Sym *from;
	const char *tosym;
	const char *fromsym;

	from = find_elf_symbol2(elf, r->r_offset, fromsec);
	fromsym = sym_name(elf, from);

	if (strstarts(fromsym, "reference___initcall"))
		return;

	tosec = sec_name(elf, get_secindex(elf, sym));
	to = find_elf_symbol(elf, r->r_addend, sym);
	tosym = sym_name(elf, to);

	/* check whitelist - we may ignore it */
	if (secref_whitelist(mismatch,
			     fromsec, fromsym, tosec, tosym)) {
		report_sec_mismatch(modname, mismatch,
				    fromsec, r->r_offset, fromsym,
				    is_function(from), tosec, tosym,
				    is_function(to));
	}
}