#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_13__ {TYPE_1__* import; scalar_t__ vaddr; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; TYPE_2__* bin; int /*<<< orphan*/  anal; int /*<<< orphan*/  config; } ;
struct TYPE_11__ {char* prefix; int /*<<< orphan*/  cur; } ;
struct TYPE_10__ {char* name; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RFlagItem ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RBinReloc ;

/* Variables and functions */
 int /*<<< orphan*/  R2_SDB_FORMAT ; 
 int R_FLAG_NAME_SIZE ; 
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  R_JOIN_4_PATHS (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  R_META_TYPE_DATA ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bin_reloc_size (TYPE_4__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_reloc_name (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_hint_set_size (int /*<<< orphan*/ ,scalar_t__,int) ; 
 char* r_bin_demangle (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,int) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r_file_exists (char*) ; 
 int /*<<< orphan*/  r_flag_item_set_realname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_flag_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_name_filter (char*,int /*<<< orphan*/ ) ; 
 int r_sandbox_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_case (char*,int) ; 
 void* r_str_newf (char*,char*,char*,...) ; 
 char* r_sys_prefix (int /*<<< orphan*/ *) ; 
 char* resolveModuleOrdinal (int /*<<< orphan*/ *,char*,int) ; 
 char* sdb_fmt (char*,char const*,...) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdb_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static void set_bin_relocs(RCore *r, RBinReloc *reloc, ut64 addr, Sdb **db, char **sdb_module) {
	int bin_demangle = r_config_get_i (r->config, "bin.demangle");
	bool keep_lib = r_config_get_i (r->config, "bin.demangle.libs");
	const char *lang = r_config_get (r->config, "bin.lang");
	char *reloc_name, *demname = NULL;
	bool is_pe = true;
	int is_sandbox = r_sandbox_enable (0);

	if (reloc->import && reloc->import->name[0]) {
		char str[R_FLAG_NAME_SIZE];
		RFlagItem *fi;

		if (is_pe && !is_sandbox && strstr (reloc->import->name, "Ordinal")) {
			const char *TOKEN = ".dll_Ordinal_";
			char *module = strdup (reloc->import->name);
			char *import = strstr (module, TOKEN);

			r_str_case (module, false);
			if (import) {
				char *filename = NULL;
				int ordinal;
				*import = 0;
				import += strlen (TOKEN);
				ordinal = atoi (import);
				if (!*sdb_module || strcmp (module, *sdb_module)) {
					sdb_free (*db);
					*db = NULL;
					free (*sdb_module);
					*sdb_module = strdup (module);
					/* always lowercase */
					filename = sdb_fmt ("%s.sdb", module);
					r_str_case (filename, false);
					if (r_file_exists (filename)) {
						*db = sdb_new (NULL, filename, 0);
					} else {
						const char *dirPrefix = r_sys_prefix (NULL);
						filename = sdb_fmt (R_JOIN_4_PATHS ("%s", R2_SDB_FORMAT, "dll", "%s.sdb"),
							dirPrefix, module);
						if (r_file_exists (filename)) {
							*db = sdb_new (NULL, filename, 0);
						}
					}
				}
				if (*db) {
					// ordinal-1 because we enumerate starting at 0
					char *symname = resolveModuleOrdinal (*db, module, ordinal - 1);  // uses sdb_get
					if (symname) {
						if (r->bin->prefix) {
							reloc->import->name = r_str_newf
								("%s.%s.%s", r->bin->prefix, module, symname);
						} else {
							reloc->import->name = r_str_newf
								("%s.%s", module, symname);
						}
						R_FREE (symname);
					}
				}
			}
			free (module);
			r_anal_hint_set_size (r->anal, reloc->vaddr, 4);
			r_meta_add (r->anal, R_META_TYPE_DATA, reloc->vaddr, reloc->vaddr+4, NULL);
		}
		reloc_name = reloc->import->name;
		if (r->bin->prefix) {
			snprintf (str, R_FLAG_NAME_SIZE, "%s.reloc.%s", r->bin->prefix, reloc_name);
		} else {
			snprintf (str, R_FLAG_NAME_SIZE, "reloc.%s", reloc_name);
		}
		if (bin_demangle) {
			demname = r_bin_demangle (r->bin->cur, lang, str, addr, keep_lib);
			if (demname) {
				snprintf (str, R_FLAG_NAME_SIZE, "reloc.%s", demname);
			}
		}
		r_name_filter (str, 0);
		fi = r_flag_set (r->flags, str, addr, bin_reloc_size (reloc));
		if (demname) {
			char *realname;
			if (r->bin->prefix) {
				realname = sdb_fmt ("%s.reloc.%s", r->bin->prefix, demname);
			} else {
				realname = sdb_fmt ("reloc.%s", demname);
			}
			r_flag_item_set_realname (fi, realname);
		}
		free (demname);
	} else {
		char *reloc_name = get_reloc_name (r, reloc, addr);
		if (reloc_name) {
			r_flag_set (r->flags, reloc_name, addr, bin_reloc_size (reloc));
		} else {
			// eprintf ("Cannot find a name for 0x%08"PFMT64x"\n", addr);
		}
	}
}