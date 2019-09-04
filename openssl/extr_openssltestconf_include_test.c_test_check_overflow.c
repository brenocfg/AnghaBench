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

__attribute__((used)) static int test_check_overflow(void)
{
#if defined(_BSD_SOURCE) \
        || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L) \
        || (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 600)
    long val = 0;
    char max[(sizeof(long) * 8) / 3 + 3];
    char *p;

    p = max + sprintf(max, "0%ld", LONG_MAX) - 1;
    setenv("FNORD", max, 1);
    if (!TEST_true(NCONF_get_number(NULL, "missing", "FNORD", &val))
            || !TEST_long_eq(val, LONG_MAX))
        return 0;

    while (++*p > '9')
        *p-- = '0';

    setenv("FNORD", max, 1);
    if (!TEST_false(NCONF_get_number(NULL, "missing", "FNORD", &val)))
        return 0;
#endif
    return 1;
}