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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  day_of_week_tests ; 
 int /*<<< orphan*/  test_days ; 
 int /*<<< orphan*/  test_x509_cmp_time ; 
 int /*<<< orphan*/  test_x509_cmp_time_current ; 
 int /*<<< orphan*/  test_x509_time ; 
 int /*<<< orphan*/  test_x509_time_print ; 
 int /*<<< orphan*/  x509_cmp_tests ; 
 int /*<<< orphan*/  x509_format_tests ; 
 int /*<<< orphan*/  x509_print_tests ; 

int setup_tests(void)
{
    ADD_TEST(test_x509_cmp_time_current);
    ADD_ALL_TESTS(test_x509_cmp_time, OSSL_NELEM(x509_cmp_tests));
    ADD_ALL_TESTS(test_x509_time, OSSL_NELEM(x509_format_tests));
    ADD_ALL_TESTS(test_days, OSSL_NELEM(day_of_week_tests));
    ADD_ALL_TESTS(test_x509_time_print, OSSL_NELEM(x509_print_tests));
    return 1;
}