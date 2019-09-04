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
struct TYPE_4__ {int /*<<< orphan*/  l; } ;
typedef  TYPE_1__ RAsmState ;

/* Variables and functions */
 int /*<<< orphan*/  R2_BINDINGS ; 
 int /*<<< orphan*/  R2_EXTRAS ; 
 int /*<<< orphan*/  R2_HOME_PLUGINS ; 
 int /*<<< orphan*/  R2_PLUGINS ; 
 char* R_LIB_ENV ; 
 int /*<<< orphan*/  R_LIB_TYPE_ANAL ; 
 int /*<<< orphan*/  R_LIB_TYPE_ASM ; 
 int /*<<< orphan*/  __lib_anal_cb ; 
 int /*<<< orphan*/  __lib_asm_cb ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_lib_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  r_lib_opendir (int /*<<< orphan*/ ,char*) ; 
 char* r_str_home (int /*<<< orphan*/ ) ; 
 char* r_str_r2_prefix (int /*<<< orphan*/ ) ; 
 char* r_sys_getenv (char*) ; 

__attribute__((used)) static void __load_plugins(RAsmState *as) {
	char *tmp = r_sys_getenv ("RASM2_NOPLUGINS");
	if (tmp) {
		free (tmp);
		return;
	}
	r_lib_add_handler (as->l, R_LIB_TYPE_ASM, "(dis)assembly plugins", &__lib_asm_cb, NULL, as);
	r_lib_add_handler (as->l, R_LIB_TYPE_ANAL, "analysis/emulation plugins", &__lib_anal_cb, NULL, as);

	char *path = r_sys_getenv (R_LIB_ENV);
	if (path && *path) {
		r_lib_opendir (as->l, path);
	}

	// load plugins from the home directory
	char *homeplugindir = r_str_home (R2_HOME_PLUGINS);
	r_lib_opendir (as->l, homeplugindir);
	free (homeplugindir);

	// load plugins from the system directory
	char *plugindir = r_str_r2_prefix (R2_PLUGINS);
	char *extrasdir = r_str_r2_prefix (R2_EXTRAS);
	char *bindingsdir = r_str_r2_prefix (R2_BINDINGS);
	r_lib_opendir (as->l, plugindir);
	r_lib_opendir (as->l, extrasdir);
	r_lib_opendir (as->l, bindingsdir);
	free (plugindir);
	free (extrasdir);
	free (bindingsdir);

	free (tmp);
	free (path);
}