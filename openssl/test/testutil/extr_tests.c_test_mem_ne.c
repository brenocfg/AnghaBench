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
 scalar_t__ memcmp (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  test_fail_memory_message (int /*<<< orphan*/ *,char const*,int,char*,char const*,char const*,char*,void const*,size_t,void const*,size_t) ; 

int test_mem_ne(const char *file, int line, const char *st1, const char *st2,
                const void *s1, size_t n1, const void *s2, size_t n2)
{
    if ((s1 == NULL) ^ (s2 == NULL))
        return 1;
    if (n1 != n2)
        return 1;
    if (s1 == NULL || memcmp(s1, s2, n1) == 0) {
        test_fail_memory_message(NULL, file, line, "memory", st1, st2, "!=",
                                 s1, n1, s2, n2);
        return 0;
    }
    return 1;
}