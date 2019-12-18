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
struct mpv_global {int dummy; } ;

/* Variables and functions */
 char* mp_find_user_config_file (int /*<<< orphan*/ *,struct mpv_global*,char*) ; 
 int /*<<< orphan*/  mp_mkdirp (char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

void mp_mk_config_dir(struct mpv_global *global, char *subdir)
{
    char *dir = mp_find_user_config_file(NULL, global, subdir);
    if (dir)
        mp_mkdirp(dir);
    talloc_free(dir);
}