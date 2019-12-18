#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* cons; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R2_HOME_THEMES ; 
 int /*<<< orphan*/  R2_THEMES ; 
 int /*<<< orphan*/  R_JOIN_2_PATHS (int /*<<< orphan*/ ,char*) ; 
 void* curtheme ; 
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ load_theme (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_cons_pal_init (int /*<<< orphan*/ ) ; 
 char* r_file_abspath (char*) ; 
 int /*<<< orphan*/  r_str_cmp (char const*,char*,int /*<<< orphan*/ ) ; 
 void* r_str_dup (void*,char*) ; 
 char* r_str_home (char*) ; 
 char* r_str_newf (int /*<<< orphan*/ ,char*) ; 
 char* r_str_r2_prefix (char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool cmd_load_theme(RCore *core, const char *_arg) {
	bool failed = false;
	char *path;
	if (!_arg || !*_arg) {
		return false;
	}
	if (!r_str_cmp (_arg, "default", strlen (_arg))) {
		curtheme = strdup (_arg);
		r_cons_pal_init (core->cons->context);
		return true;
	}
	char *arg = strdup (_arg);

	char *tmp = r_str_newf (R_JOIN_2_PATHS (R2_HOME_THEMES, "%s"), arg);
	char *home = tmp ? r_str_home (tmp) : NULL;
	free (tmp);

	tmp = r_str_newf (R_JOIN_2_PATHS (R2_THEMES, "%s"), arg);
	path = tmp ? r_str_r2_prefix (tmp) : NULL;
	free (tmp);

	if (!load_theme (core, home)) {
		if (load_theme (core, path)) {
			curtheme = r_str_dup (curtheme, arg);
		} else {
			if (load_theme (core, arg)) {
				curtheme = r_str_dup (curtheme, arg);
			} else {
				char *absfile = r_file_abspath (arg);
				eprintf ("eco: cannot open colorscheme profile (%s)\n", absfile);
				free (absfile);
				failed = true;
			}
		}
	}
	free (home);
	free (path);
	free (arg);
	return !failed;
}