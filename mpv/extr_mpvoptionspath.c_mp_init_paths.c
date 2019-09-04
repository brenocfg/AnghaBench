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
struct mpv_global {int /*<<< orphan*/  configdir; } ;
struct MPOpts {char* force_configdir; int /*<<< orphan*/  load_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  talloc_strdup (struct mpv_global*,char const*) ; 

void mp_init_paths(struct mpv_global *global, struct MPOpts *opts)
{
    TA_FREEP(&global->configdir);

    const char *force_configdir = getenv("MPV_HOME");
    if (opts->force_configdir && opts->force_configdir[0])
        force_configdir = opts->force_configdir;
    if (!opts->load_config)
        force_configdir = "";

    global->configdir = talloc_strdup(global, force_configdir);
}