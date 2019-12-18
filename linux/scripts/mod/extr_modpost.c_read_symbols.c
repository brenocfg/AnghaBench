#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct symbol {scalar_t__ is_static; } ;
struct module {int skip; int gpl_compatible; int /*<<< orphan*/  unres; int /*<<< orphan*/  srcversion; int /*<<< orphan*/  imported_namespaces; } ;
struct elf_info {scalar_t__ hdr; int /*<<< orphan*/  modinfo; scalar_t__ strtab; TYPE_1__* symtab_stop; TYPE_1__* symtab_start; } ;
struct TYPE_5__ {scalar_t__ st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Sym ;

/* Variables and functions */
 unsigned char ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 unsigned char STB_GLOBAL ; 
 unsigned char STB_WEAK ; 
 int /*<<< orphan*/  add_namespace (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ all_versions ; 
 int /*<<< orphan*/  alloc_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_sec_ref (struct module*,char const*,struct elf_info*) ; 
 struct symbol* find_symbol (char*) ; 
 char* get_modinfo (struct elf_info*,char*) ; 
 char* get_next_modinfo (struct elf_info*,char*,char*) ; 
 int /*<<< orphan*/  get_src_version (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handle_moddevtable (struct module*,struct elf_info*,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  handle_modversions (struct module*,struct elf_info*,TYPE_1__*,char const*) ; 
 int have_vmlinux ; 
 scalar_t__ is_vmlinux (char const*) ; 
 scalar_t__ license_is_gpl_compatible (char*) ; 
 int /*<<< orphan*/  maybe_frob_rcs_version (char const*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ modversions ; 
 int /*<<< orphan*/  namespace_from_kstrtabns (struct elf_info*,TYPE_1__*) ; 
 struct module* new_module (char const*) ; 
 int /*<<< orphan*/  parse_elf (struct elf_info*,char const*) ; 
 int /*<<< orphan*/  parse_elf_finish (struct elf_info*) ; 
 char* remove_dot (scalar_t__) ; 
 int strlen (char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 
 int /*<<< orphan*/  sym_update_namespace (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vmlinux_section_warnings ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void read_symbols(const char *modname)
{
	const char *symname;
	char *version;
	char *license;
	char *namespace;
	struct module *mod;
	struct elf_info info = { };
	Elf_Sym *sym;

	if (!parse_elf(&info, modname))
		return;

	mod = new_module(modname);

	/* When there's no vmlinux, don't print warnings about
	 * unresolved symbols (since there'll be too many ;) */
	if (is_vmlinux(modname)) {
		have_vmlinux = 1;
		mod->skip = 1;
	}

	license = get_modinfo(&info, "license");
	if (!license && !is_vmlinux(modname))
		warn("modpost: missing MODULE_LICENSE() in %s\n"
		     "see include/linux/module.h for "
		     "more information\n", modname);
	while (license) {
		if (license_is_gpl_compatible(license))
			mod->gpl_compatible = 1;
		else {
			mod->gpl_compatible = 0;
			break;
		}
		license = get_next_modinfo(&info, "license", license);
	}

	namespace = get_modinfo(&info, "import_ns");
	while (namespace) {
		add_namespace(&mod->imported_namespaces, namespace);
		namespace = get_next_modinfo(&info, "import_ns", namespace);
	}

	for (sym = info.symtab_start; sym < info.symtab_stop; sym++) {
		symname = remove_dot(info.strtab + sym->st_name);

		handle_modversions(mod, &info, sym, symname);
		handle_moddevtable(mod, &info, sym, symname);
	}

	/* Apply symbol namespaces from __kstrtabns_<symbol> entries. */
	for (sym = info.symtab_start; sym < info.symtab_stop; sym++) {
		symname = remove_dot(info.strtab + sym->st_name);

		if (strstarts(symname, "__kstrtabns_"))
			sym_update_namespace(symname + strlen("__kstrtabns_"),
					     namespace_from_kstrtabns(&info,
								      sym));
	}

	// check for static EXPORT_SYMBOL_* functions && global vars
	for (sym = info.symtab_start; sym < info.symtab_stop; sym++) {
		unsigned char bind = ELF_ST_BIND(sym->st_info);

		if (bind == STB_GLOBAL || bind == STB_WEAK) {
			struct symbol *s =
				find_symbol(remove_dot(info.strtab +
						       sym->st_name));

			if (s)
				s->is_static = 0;
		}
	}

	if (!is_vmlinux(modname) || vmlinux_section_warnings)
		check_sec_ref(mod, modname, &info);

	version = get_modinfo(&info, "version");
	if (version)
		maybe_frob_rcs_version(modname, version, info.modinfo,
				       version - (char *)info.hdr);
	if (version || (all_versions && !is_vmlinux(modname)))
		get_src_version(modname, mod->srcversion,
				sizeof(mod->srcversion)-1);

	parse_elf_finish(&info);

	/* Our trick to get versioning for module struct etc. - it's
	 * never passed as an argument to an exported function, so
	 * the automatic versioning doesn't pick it up, but it's really
	 * important anyhow */
	if (modversions)
		mod->unres = alloc_symbol("module_layout", 0, mod->unres);
}