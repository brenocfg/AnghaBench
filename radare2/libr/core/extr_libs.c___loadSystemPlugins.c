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
struct TYPE_4__ {int /*<<< orphan*/  lib; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R2_BINDINGS ; 
 int /*<<< orphan*/  R2_EXTRAS ; 
 int /*<<< orphan*/  R2_HOME_PLUGINS ; 
 int /*<<< orphan*/  R2_PLUGINS ; 
 int R_CORE_LOADLIBS_CONFIG ; 
 int R_CORE_LOADLIBS_ENV ; 
 int R_CORE_LOADLIBS_HOME ; 
 int R_CORE_LOADLIBS_SYSTEM ; 
 int /*<<< orphan*/  R_LIB_ENV ; 
 int /*<<< orphan*/  __openPluginsAt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_lib_opendir (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_home (int /*<<< orphan*/ ) ; 
 char* r_sys_getenv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __loadSystemPlugins(RCore *core, int where, const char *path) {
#if R2_LOADLIBS
	if (!where) {
		where = -1;
	}
	if (path) {
		r_lib_opendir (core->lib, path);
	}
	if (where & R_CORE_LOADLIBS_CONFIG) {
		r_lib_opendir (core->lib, r_config_get (core->config, "dir.plugins"));
	}
	if (where & R_CORE_LOADLIBS_ENV) {
		char *p = r_sys_getenv (R_LIB_ENV);
		if (p && *p) {
			r_lib_opendir (core->lib, p);
		}
		free (p);
	}
	if (where & R_CORE_LOADLIBS_HOME) {
		char *hpd = r_str_home (R2_HOME_PLUGINS);
		if (hpd) {
			r_lib_opendir (core->lib, hpd);
			free (hpd);
		}
	}
	if (where & R_CORE_LOADLIBS_SYSTEM) {
		__openPluginsAt (core, R2_PLUGINS);
		__openPluginsAt (core, R2_EXTRAS);
		__openPluginsAt (core, R2_BINDINGS);
	}
#endif
}