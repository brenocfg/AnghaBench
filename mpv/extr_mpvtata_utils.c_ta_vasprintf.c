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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  ta_free (char*) ; 
 int /*<<< orphan*/  ta_set_parent (char*,void*) ; 
 int /*<<< orphan*/  ta_vasprintf_append_at (char**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

char *ta_vasprintf(void *ta_parent, const char *fmt, va_list ap)
{
    char *res = NULL;
    ta_vasprintf_append_at(&res, 0, fmt, ap);
    if (!res || !ta_set_parent(res, ta_parent)) {
        ta_free(res);
        return NULL;
    }
    return res;
}