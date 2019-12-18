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
struct dstr {char* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcrash (char*) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char*) ; 
 char* getenv (char*) ; 

char *os_get_config_path_ptr(const char *name)
{
#ifdef USE_XDG
	struct dstr path;
	char *xdg_ptr = getenv("XDG_CONFIG_HOME");

	/* If XDG_CONFIG_HOME is unset,
	 * we use the default $HOME/.config/[name] instead */
	if (xdg_ptr == NULL) {
		char *home_ptr = getenv("HOME");
		if (home_ptr == NULL)
			bcrash("Could not get $HOME\n");

		dstr_init_copy(&path, home_ptr);
		dstr_cat(&path, "/.config/");
		dstr_cat(&path, name);
	} else {
		dstr_init_copy(&path, xdg_ptr);
		dstr_cat(&path, "/");
		dstr_cat(&path, name);
	}
	return path.array;
#else
	char *path_ptr = getenv("HOME");
	if (path_ptr == NULL)
		bcrash("Could not get $HOME\n");

	struct dstr path;
	dstr_init_copy(&path, path_ptr);
	dstr_cat(&path, "/.");
	dstr_cat(&path, name);
	return path.array;
#endif
}