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
 int /*<<< orphan*/  MP_DBG (struct mpv_global*,char*,char const*,char*) ; 
 int /*<<< orphan*/ * config_dirs ; 
 scalar_t__ mp_get_platform_path (void*,struct mpv_global*,int /*<<< orphan*/ ) ; 
 char* mp_path_join (void*,char*,char const*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

char *mp_find_user_config_file(void *talloc_ctx, struct mpv_global *global,
                               const char *filename)
{
    void *tmp = talloc_new(NULL);
    char *res = (char *)mp_get_platform_path(tmp, global, config_dirs[0]);
    if (res)
        res = mp_path_join(talloc_ctx, res, filename);
    talloc_free(tmp);
    MP_DBG(global, "config path: '%s' -> '%s'\n", filename, res ? res : "-");
    return res;
}