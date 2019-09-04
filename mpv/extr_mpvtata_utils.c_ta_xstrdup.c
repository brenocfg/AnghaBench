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
 int /*<<< orphan*/  ta_oom_b (int /*<<< orphan*/ ) ; 
 char* ta_strdup (void*,char const*) ; 

char *ta_xstrdup(void *ta_parent, const char *str)
{
    char *res = ta_strdup(ta_parent, str);
    ta_oom_b(res || !str);
    return res;
}