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
 char* mp_get_win_exe_subdir (void*,char*) ; 
 scalar_t__ mp_path_exists (char*) ; 
 int /*<<< orphan*/  portable_path ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void path_init(void)
{
    void *tmp = talloc_new(NULL);
    char *path = mp_get_win_exe_subdir(tmp, "portable_config");
    if (path && mp_path_exists(path))
        portable_path = talloc_strdup(NULL, path);
    talloc_free(tmp);
}