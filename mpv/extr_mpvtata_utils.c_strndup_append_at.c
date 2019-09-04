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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strnlen (char const*,size_t) ; 
 int /*<<< orphan*/  ta_dbg_mark_as_string (char*) ; 
 size_t ta_get_size (char*) ; 
 char* ta_realloc_size (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static bool strndup_append_at(char **str, size_t at, const char *append,
                              size_t append_len)
{
    assert(ta_get_size(*str) >= at);

    if (!*str && !append)
        return true; // stays NULL, but not an OOM condition

    size_t real_len = append ? strnlen(append, append_len) : 0;
    if (append_len > real_len)
        append_len = real_len;

    if (ta_get_size(*str) < at + append_len + 1) {
        char *t = ta_realloc_size(NULL, *str, at + append_len + 1);
        if (!t)
            return false;
        *str = t;
    }

    if (append_len)
        memcpy(*str + at, append, append_len);

    (*str)[at + append_len] = '\0';

    ta_dbg_mark_as_string(*str);

    return true;
}