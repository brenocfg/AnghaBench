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
struct mpv_global {int /*<<< orphan*/  log; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  mp_err (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* mp_get_user_path (void*,struct mpv_global*,char*) ; 
 int /*<<< orphan*/  mp_msg_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void reopen_file(char *opt, char **current_path, FILE **file,
                        const char *type, struct mpv_global *global)
{
    void *tmp = talloc_new(NULL);
    bool fail = false;

    char *new_path = mp_get_user_path(tmp, global, opt);
    if (!new_path)
        new_path = "";

    pthread_mutex_lock(&mp_msg_lock); // for *current_path/*file

    char *old_path = *current_path ? *current_path : "";
    if (strcmp(old_path, new_path) != 0) {
        if (*file)
            fclose(*file);
        *file = NULL;
        talloc_free(*current_path);
        *current_path = talloc_strdup(NULL, new_path);
        if (new_path[0]) {
            *file = fopen(new_path, "wb");
            fail = !*file;
        }
    }

    pthread_mutex_unlock(&mp_msg_lock);

    if (fail)
        mp_err(global->log, "Failed to open %s file '%s'\n", type, new_path);

    talloc_free(tmp);
}