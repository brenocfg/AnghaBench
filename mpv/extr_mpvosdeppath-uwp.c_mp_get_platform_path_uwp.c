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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 scalar_t__ GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 int _MAX_PATH ; 
 char const* mp_to_utf8 (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *mp_get_platform_path_uwp(void *talloc_ctx, const char *type)
{
    if (strcmp(type, "home") == 0) {
        wchar_t homeDir[_MAX_PATH];
        if (GetCurrentDirectoryW(_MAX_PATH, homeDir) != 0)
            return mp_to_utf8(talloc_ctx, homeDir);
    }
    return NULL;
}