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
 int /*<<< orphan*/  mp_get_win_exe_dir (void*) ; 
 char* talloc_asprintf (void*,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static char *mp_get_win_exe_subdir(void *ta_ctx, const char *name)
{
    return talloc_asprintf(ta_ctx, "%s/%s", mp_get_win_exe_dir(ta_ctx), name);
}