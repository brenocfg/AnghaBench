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
struct MPContext {int /*<<< orphan*/  global; TYPE_1__* opts; } ;
struct TYPE_2__ {char** script_files; int /*<<< orphan*/  auto_load_scripts; } ;

/* Variables and functions */
 char** list_script_files (void*,char*) ; 
 char** mp_find_all_config_files (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_load_script (struct MPContext*,char*) ; 
 int /*<<< orphan*/  mp_load_user_script (struct MPContext*,char*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

void mp_load_scripts(struct MPContext *mpctx)
{
    // Load scripts from options
    char **files = mpctx->opts->script_files;
    for (int n = 0; files && files[n]; n++) {
        if (files[n][0])
            mp_load_user_script(mpctx, files[n]);
    }
    if (!mpctx->opts->auto_load_scripts)
        return;

    // Load all scripts
    void *tmp = talloc_new(NULL);
    char **scriptsdir = mp_find_all_config_files(tmp, mpctx->global, "scripts");
    for (int i = 0; scriptsdir && scriptsdir[i]; i++) {
        files = list_script_files(tmp, scriptsdir[i]);
        for (int n = 0; files && files[n]; n++)
            mp_load_script(mpctx, files[n]);
    }
    talloc_free(tmp);
}