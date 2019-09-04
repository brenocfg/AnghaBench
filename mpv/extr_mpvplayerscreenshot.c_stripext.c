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
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 char* talloc_asprintf (void*,char*,int,char const*) ; 

__attribute__((used)) static char *stripext(void *talloc_ctx, const char *s)
{
    const char *end = strrchr(s, '.');
    if (!end)
        end = s + strlen(s);
    return talloc_asprintf(talloc_ctx, "%.*s", (int)(end - s), s);
}