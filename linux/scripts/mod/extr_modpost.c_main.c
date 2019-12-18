#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {int /*<<< orphan*/  export; TYPE_1__* module; int /*<<< orphan*/  name; scalar_t__ is_static; struct symbol* next; } ;
struct module {char* name; scalar_t__ skip; struct module* next; } ;
struct ext_sym_list {char* file; struct ext_sym_list* next; } ;
struct buffer {struct ext_sym_list* p; scalar_t__ pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  is_dot_o; } ;

/* Variables and functions */
 struct ext_sym_list* NOFAIL (int /*<<< orphan*/ ) ; 
 int PATH_MAX ; 
 int SYMBOL_HASH_SIZE ; 
 int /*<<< orphan*/  add_depends (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_header (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_intree_flag (struct buffer*,int) ; 
 int /*<<< orphan*/  add_moddevtable (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_retpoline (struct buffer*) ; 
 int /*<<< orphan*/  add_srcversion (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_staging_flag (struct buffer*,char*) ; 
 int add_versions (struct buffer*,struct module*) ; 
 int all_versions ; 
 int check_exports (struct module*) ; 
 int check_modname_len (struct module*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  export_str (int /*<<< orphan*/ ) ; 
 int external_module ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (struct ext_sym_list*) ; 
 int getopt (int,char**,char*) ; 
 int ignore_missing_files ; 
 scalar_t__ is_vmlinux (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 struct module* modules ; 
 int modversions ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  read_dump (char*,int) ; 
 int /*<<< orphan*/  read_symbols (char*) ; 
 int /*<<< orphan*/  read_symbols_from_files (char*) ; 
 scalar_t__ sec_mismatch_count ; 
 int sec_mismatch_fatal ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct symbol** symbolhash ; 
 int /*<<< orphan*/  vmlinux_section_warnings ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int warn_unresolved ; 
 int /*<<< orphan*/  write_dump (char*) ; 
 int /*<<< orphan*/  write_if_changed (struct buffer*,char*) ; 
 int write_namespace_deps ; 
 int /*<<< orphan*/  write_namespace_deps_files () ; 

int main(int argc, char **argv)
{
	struct module *mod;
	struct buffer buf = { };
	char *kernel_read = NULL, *module_read = NULL;
	char *dump_write = NULL, *files_source = NULL;
	int opt;
	int err;
	int n;
	struct ext_sym_list *extsym_iter;
	struct ext_sym_list *extsym_start = NULL;

	while ((opt = getopt(argc, argv, "i:I:e:mnsT:o:awEd")) != -1) {
		switch (opt) {
		case 'i':
			kernel_read = optarg;
			break;
		case 'I':
			module_read = optarg;
			external_module = 1;
			break;
		case 'e':
			external_module = 1;
			extsym_iter =
			   NOFAIL(malloc(sizeof(*extsym_iter)));
			extsym_iter->next = extsym_start;
			extsym_iter->file = optarg;
			extsym_start = extsym_iter;
			break;
		case 'm':
			modversions = 1;
			break;
		case 'n':
			ignore_missing_files = 1;
			break;
		case 'o':
			dump_write = optarg;
			break;
		case 'a':
			all_versions = 1;
			break;
		case 's':
			vmlinux_section_warnings = 0;
			break;
		case 'T':
			files_source = optarg;
			break;
		case 'w':
			warn_unresolved = 1;
			break;
		case 'E':
			sec_mismatch_fatal = 1;
			break;
		case 'd':
			write_namespace_deps = 1;
			break;
		default:
			exit(1);
		}
	}

	if (kernel_read)
		read_dump(kernel_read, 1);
	if (module_read)
		read_dump(module_read, 0);
	while (extsym_start) {
		read_dump(extsym_start->file, 0);
		extsym_iter = extsym_start->next;
		free(extsym_start);
		extsym_start = extsym_iter;
	}

	while (optind < argc)
		read_symbols(argv[optind++]);

	if (files_source)
		read_symbols_from_files(files_source);

	err = 0;

	for (mod = modules; mod; mod = mod->next) {
		char fname[PATH_MAX];

		if (mod->skip)
			continue;

		buf.pos = 0;

		err |= check_modname_len(mod);
		err |= check_exports(mod);
		if (write_namespace_deps)
			continue;

		add_header(&buf, mod);
		add_intree_flag(&buf, !external_module);
		add_retpoline(&buf);
		add_staging_flag(&buf, mod->name);
		err |= add_versions(&buf, mod);
		add_depends(&buf, mod);
		add_moddevtable(&buf, mod);
		add_srcversion(&buf, mod);

		sprintf(fname, "%s.mod.c", mod->name);
		write_if_changed(&buf, fname);
	}

	if (write_namespace_deps) {
		write_namespace_deps_files();
		return 0;
	}

	if (dump_write)
		write_dump(dump_write);
	if (sec_mismatch_count && sec_mismatch_fatal)
		fatal("modpost: Section mismatches detected.\n"
		      "Set CONFIG_SECTION_MISMATCH_WARN_ONLY=y to allow them.\n");
	for (n = 0; n < SYMBOL_HASH_SIZE; n++) {
		struct symbol *s;

		for (s = symbolhash[n]; s; s = s->next) {
			/*
			 * Do not check "vmlinux". This avoids the same warnings
			 * shown twice, and false-positives for ARCH=um.
			 */
			if (is_vmlinux(s->module->name) && !s->module->is_dot_o)
				continue;

			if (s->is_static)
				warn("\"%s\" [%s] is a static %s\n",
				     s->name, s->module->name,
				     export_str(s->export));
		}
	}

	free(buf.p);

	return err;
}