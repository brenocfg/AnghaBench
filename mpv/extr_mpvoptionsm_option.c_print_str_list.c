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
 char** VAL (void const*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 
 char* talloc_strdup_append_buffer (char*,char*) ; 

__attribute__((used)) static char *print_str_list(const m_option_t *opt, const void *src)
{
    char **lst = NULL;
    char *ret = NULL;

    if (!(src && VAL(src)))
        return talloc_strdup(NULL, "");
    lst = VAL(src);

    for (int i = 0; lst[i]; i++) {
        if (ret)
            ret = talloc_strdup_append_buffer(ret, ",");
        ret = talloc_strdup_append_buffer(ret, lst[i]);
    }
    return ret;
}