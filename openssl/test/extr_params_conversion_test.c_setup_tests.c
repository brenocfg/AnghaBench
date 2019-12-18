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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  run_param_file_tests ; 
 size_t test_get_argument_count () ; 

int setup_tests(void)
{
    size_t n = test_get_argument_count();

    if (n == 0)
        return 0;

#if !defined(OPENSSL_NO_INTTYPES_H)
    ADD_ALL_TESTS(run_param_file_tests, n);
#endif /* OPENSSL_NO_INTTYPES_H */

    return 1;
}