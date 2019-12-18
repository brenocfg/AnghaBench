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
 int /*<<< orphan*/  FOLDERID_RoamingAppData ; 
 char* mp_get_win_shell_dir (void*,int /*<<< orphan*/ *) ; 
 char* mp_path_join (void*,char*,char*) ; 

__attribute__((used)) static char *mp_get_win_app_dir(void *talloc_ctx)
{
    char *path = mp_get_win_shell_dir(talloc_ctx, &FOLDERID_RoamingAppData);
    return path ? mp_path_join(talloc_ctx, path, "mpv") : NULL;
}