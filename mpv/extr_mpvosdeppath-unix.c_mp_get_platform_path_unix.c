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
 char const* MPV_CONFDIR ; 
 char const* getenv (char*) ; 
 char const* mpv_home ; 
 char const* old_home ; 
 int /*<<< orphan*/  path_init ; 
 int /*<<< orphan*/  path_init_once ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *mp_get_platform_path_unix(void *talloc_ctx, const char *type)
{
    pthread_once(&path_init_once, path_init);
    if (strcmp(type, "home") == 0)
        return mpv_home;
    if (strcmp(type, "old_home") == 0)
        return old_home;
    if (strcmp(type, "global") == 0)
        return MPV_CONFDIR;
    if (strcmp(type, "desktop") == 0)
        return getenv("HOME");
    return NULL;
}