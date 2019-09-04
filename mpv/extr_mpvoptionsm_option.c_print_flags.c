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
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 char* find_next_flag (int /*<<< orphan*/  const*,int*) ; 
 char* talloc_asprintf_append_buffer (char*,char*,char*,char const*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *print_flags(const m_option_t *opt, const void *val)
{
    int value = *(int *)val;
    char *res = talloc_strdup(NULL, "");
    while (1) {
        const char *flag = find_next_flag(opt, &value);
        if (!flag)
            break;

        res = talloc_asprintf_append_buffer(res, "%s%s", res[0] ? "+" : "", flag);
    }
    return res;
}