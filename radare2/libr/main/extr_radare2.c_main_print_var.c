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

/* Variables and functions */
 int /*<<< orphan*/  R2_HOME_CACHEDIR ; 
 int /*<<< orphan*/  R2_HOME_CONFIGDIR ; 
 int /*<<< orphan*/  R2_HOME_DATADIR ; 
 int /*<<< orphan*/  R2_HOME_PLUGINS ; 
 int /*<<< orphan*/  R2_HOME_ZIGNS ; 
 int /*<<< orphan*/  R2_INCDIR ; 
 int /*<<< orphan*/  R2_LIBDIR ; 
 int /*<<< orphan*/  R2_PLUGINS ; 
 char* R2_PREFIX ; 
 int /*<<< orphan*/  R2_SDB_MAGIC ; 
 char* R_LIB_EXT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* r_str_home (int /*<<< orphan*/ ) ; 
 char* r_str_r2_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int main_print_var(const char *var_name) {
	int i = 0;
#ifdef __WINDOWS__
	char *incdir = r_str_r2_prefix (R2_INCDIR);
	char *libdir = r_str_r2_prefix (R2_LIBDIR);
#else
	char *incdir = strdup (R2_INCDIR);
	char *libdir = strdup (R2_LIBDIR);
#endif
	char *confighome = r_str_home (R2_HOME_CONFIGDIR);
	char *datahome = r_str_home (R2_HOME_DATADIR);
	char *cachehome = r_str_home (R2_HOME_CACHEDIR);
	char *homeplugins = r_str_home (R2_HOME_PLUGINS);
	char *homezigns = r_str_home (R2_HOME_ZIGNS);
	char *plugins = r_str_r2_prefix (R2_PLUGINS);
	char *magicpath = r_str_r2_prefix (R2_SDB_MAGIC);
	struct radare2_var_t {
		const char *name;
		const char *value;
	} r2_vars[] = {
		{ "R2_PREFIX", R2_PREFIX },
		{ "R2_MAGICPATH", magicpath },
		{ "R2_PREFIX", R2_PREFIX },
		{ "R2_INCDIR", incdir },
		{ "R2_LIBDIR", libdir },
		{ "R2_LIBEXT", R_LIB_EXT },
		{ "R2_RCONFIGHOME", confighome },
		{ "R2_RDATAHOME", datahome },
		{ "R2_RCACHEHOME", cachehome },
		{ "R2_LIBR_PLUGINS", plugins },
		{ "R2_USER_PLUGINS", homeplugins },
		{ "R2_USER_ZIGNS", homezigns },
		{ NULL, NULL }
	};
	int delta = 0;
	if (var_name && strncmp (var_name, "R2_", 3)) {
		delta = 3;
	}
	if (var_name) {
		while (r2_vars[i].name) {
			if (!strcmp (r2_vars[i].name + delta, var_name)) {
				printf ("%s\n", r2_vars[i].value);
				break;
			}
			i++;
		}
	} else {
		while (r2_vars[i].name) {
			printf ("%s=%s\n", r2_vars[i].name, r2_vars[i].value);
			i++;
		}
	}
	free (incdir);
	free (libdir);
	free (confighome);
	free (datahome);
	free (cachehome);
	free (homeplugins);
	free (homezigns);
	free (plugins);
	free (magicpath);
	return 0;
}