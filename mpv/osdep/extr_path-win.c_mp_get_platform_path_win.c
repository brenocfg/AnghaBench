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
 int /*<<< orphan*/  FOLDERID_Desktop ; 
 char const* mp_get_win_app_dir (void*) ; 
 char const* mp_get_win_exe_dir (void*) ; 
 char const* mp_get_win_exe_subdir (void*,char*) ; 
 char const* mp_get_win_shell_dir (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_init ; 
 int /*<<< orphan*/  path_init_once ; 
 char const* portable_path ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *mp_get_platform_path_win(void *talloc_ctx, const char *type)
{
    pthread_once(&path_init_once, path_init);
    if (portable_path) {
        if (strcmp(type, "home") == 0)
            return portable_path;
    } else {
        if (strcmp(type, "home") == 0)
            return mp_get_win_app_dir(talloc_ctx);
        if (strcmp(type, "old_home") == 0)
            return mp_get_win_exe_dir(talloc_ctx);
        // Not really true, but serves as a way to return a lowest-priority dir.
        if (strcmp(type, "global") == 0)
            return mp_get_win_exe_subdir(talloc_ctx, "mpv");
    }
    if (strcmp(type, "desktop") == 0)
        return mp_get_win_shell_dir(talloc_ctx, &FOLDERID_Desktop);
    return NULL;
}