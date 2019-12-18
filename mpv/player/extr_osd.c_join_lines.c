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
 char* talloc_asprintf_append (char*,char*,char*,char*) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static char *join_lines(void *ta_ctx, char **parts, int num_parts)
{
    char *res = talloc_strdup(ta_ctx, "");
    for (int n = 0; n < num_parts; n++)
        res = talloc_asprintf_append(res, "%s%s", n ? "\n" : "", parts[n]);
    return res;
}