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
struct coro {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIKELY (char*) ; 
 char* coro_malloc (struct coro*,size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 int strnlen (char const*,size_t) ; 

char *coro_strndup(struct coro *coro, const char *str, size_t max_len)
{
    const size_t len = strnlen(str, max_len) + 1;
    char *dup = coro_malloc(coro, len);

    if (LIKELY(dup)) {
        memcpy(dup, str, len);
        dup[len - 1] = '\0';
    }
    return dup;
}