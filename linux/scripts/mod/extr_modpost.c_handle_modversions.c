#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct module {int has_init; int has_cleanup; int /*<<< orphan*/  unres; int /*<<< orphan*/  name; scalar_t__ is_dot_o; } ;
struct elf_info {TYPE_2__* hdr; TYPE_1__* sechdrs; } ;
typedef  enum export { ____Placeholder_export } export ;
struct TYPE_8__ {int st_value; int st_shndx; int /*<<< orphan*/  st_info; } ;
struct TYPE_7__ {scalar_t__ e_type; int /*<<< orphan*/  e_machine; } ;
struct TYPE_6__ {int sh_offset; int sh_addr; } ;
typedef  TYPE_3__ Elf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_SPARC ; 
 int /*<<< orphan*/  EM_SPARCV9 ; 
 scalar_t__ ET_REL ; 
 char* NOFAIL (int /*<<< orphan*/ ) ; 
 int SHN_ABS ; 
#define  SHN_COMMON 129 
#define  SHN_UNDEF 128 
 int /*<<< orphan*/  STB_GLOBAL ; 
 int /*<<< orphan*/  STB_WEAK ; 
 int /*<<< orphan*/  STT_SPARC_REGISTER ; 
 unsigned int TO_NATIVE (unsigned int) ; 
 int /*<<< orphan*/  alloc_symbol (char const*,int,int /*<<< orphan*/ ) ; 
 int export_from_sec (struct elf_info*,int /*<<< orphan*/ ) ; 
 int export_from_secname (struct elf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_secindex (struct elf_info*,TYPE_3__*) ; 
 int /*<<< orphan*/  ignore_undef_symbol (struct elf_info*,char const*) ; 
 scalar_t__ is_vmlinux (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 
 int /*<<< orphan*/  sym_add_exported (char const*,struct module*,int) ; 
 int /*<<< orphan*/  sym_update_crc (char const*,struct module*,unsigned int,int) ; 
 char toupper (char) ; 
 int /*<<< orphan*/  warn (char*,char const*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void handle_modversions(struct module *mod, struct elf_info *info,
			       Elf_Sym *sym, const char *symname)
{
	unsigned int crc;
	enum export export;
	bool is_crc = false;
	const char *name;

	if ((!is_vmlinux(mod->name) || mod->is_dot_o) &&
	    strstarts(symname, "__ksymtab"))
		export = export_from_secname(info, get_secindex(info, sym));
	else
		export = export_from_sec(info, get_secindex(info, sym));

	/* CRC'd symbol */
	if (strstarts(symname, "__crc_")) {
		is_crc = true;
		crc = (unsigned int) sym->st_value;
		if (sym->st_shndx != SHN_UNDEF && sym->st_shndx != SHN_ABS) {
			unsigned int *crcp;

			/* symbol points to the CRC in the ELF object */
			crcp = (void *)info->hdr + sym->st_value +
			       info->sechdrs[sym->st_shndx].sh_offset -
			       (info->hdr->e_type != ET_REL ?
				info->sechdrs[sym->st_shndx].sh_addr : 0);
			crc = TO_NATIVE(*crcp);
		}
		sym_update_crc(symname + strlen("__crc_"), mod, crc,
				export);
	}

	switch (sym->st_shndx) {
	case SHN_COMMON:
		if (strstarts(symname, "__gnu_lto_")) {
			/* Should warn here, but modpost runs before the linker */
		} else
			warn("\"%s\" [%s] is COMMON symbol\n", symname, mod->name);
		break;
	case SHN_UNDEF:
		/* undefined symbol */
		if (ELF_ST_BIND(sym->st_info) != STB_GLOBAL &&
		    ELF_ST_BIND(sym->st_info) != STB_WEAK)
			break;
		if (ignore_undef_symbol(info, symname))
			break;
/* cope with newer glibc (2.3.4 or higher) STT_ definition in elf.h */
#if defined(STT_REGISTER) || defined(STT_SPARC_REGISTER)
/* add compatibility with older glibc */
#ifndef STT_SPARC_REGISTER
#define STT_SPARC_REGISTER STT_REGISTER
#endif
		if (info->hdr->e_machine == EM_SPARC ||
		    info->hdr->e_machine == EM_SPARCV9) {
			/* Ignore register directives. */
			if (ELF_ST_TYPE(sym->st_info) == STT_SPARC_REGISTER)
				break;
			if (symname[0] == '.') {
				char *munged = NOFAIL(strdup(symname));
				munged[0] = '_';
				munged[1] = toupper(munged[1]);
				symname = munged;
			}
		}
#endif

		if (is_crc) {
			const char *e = is_vmlinux(mod->name) ?"":".ko";
			warn("EXPORT symbol \"%s\" [%s%s] version generation failed, symbol will not be versioned.\n",
			     symname + strlen("__crc_"), mod->name, e);
		}
		mod->unres = alloc_symbol(symname,
					  ELF_ST_BIND(sym->st_info) == STB_WEAK,
					  mod->unres);
		break;
	default:
		/* All exported symbols */
		if (strstarts(symname, "__ksymtab_")) {
			name = symname + strlen("__ksymtab_");
			sym_add_exported(name, mod, export);
		}
		if (strcmp(symname, "init_module") == 0)
			mod->has_init = 1;
		if (strcmp(symname, "cleanup_module") == 0)
			mod->has_cleanup = 1;
		break;
	}
}