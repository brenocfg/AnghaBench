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
struct tep_handle {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_PLUGIN_DIR ; 
 char* PLUGIN_DIR ; 
 int TEP_DISABLE_PLUGINS ; 
 int TEP_DISABLE_SYS_PLUGINS ; 
 int asprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  load_plugins_dir (struct tep_handle*,char const*,char*,void (*) (struct tep_handle*,char const*,char const*,void*),void*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
load_plugins(struct tep_handle *tep, const char *suffix,
	     void (*load_plugin)(struct tep_handle *tep,
				 const char *path,
				 const char *name,
				 void *data),
	     void *data)
{
	char *home;
	char *path;
	char *envdir;
	int ret;

	if (tep->flags & TEP_DISABLE_PLUGINS)
		return;

	/*
	 * If a system plugin directory was defined,
	 * check that first.
	 */
#ifdef PLUGIN_DIR
	if (!(tep->flags & TEP_DISABLE_SYS_PLUGINS))
		load_plugins_dir(tep, suffix, PLUGIN_DIR,
				 load_plugin, data);
#endif

	/*
	 * Next let the environment-set plugin directory
	 * override the system defaults.
	 */
	envdir = getenv("TRACEEVENT_PLUGIN_DIR");
	if (envdir)
		load_plugins_dir(tep, suffix, envdir, load_plugin, data);

	/*
	 * Now let the home directory override the environment
	 * or system defaults.
	 */
	home = getenv("HOME");
	if (!home)
		return;

	ret = asprintf(&path, "%s/%s", home, LOCAL_PLUGIN_DIR);
	if (ret < 0) {
		warning("could not allocate plugin memory\n");
		return;
	}

	load_plugins_dir(tep, suffix, path, load_plugin, data);

	free(path);
}