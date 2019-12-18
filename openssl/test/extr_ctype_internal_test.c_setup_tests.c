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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  case_change ; 
 int /*<<< orphan*/  test_ctype_chars ; 
 int /*<<< orphan*/  test_ctype_eof ; 
 int /*<<< orphan*/  test_ctype_tolower ; 
 int /*<<< orphan*/  test_ctype_toupper ; 

int setup_tests(void)
{
    ADD_ALL_TESTS(test_ctype_chars, 256);
    ADD_ALL_TESTS(test_ctype_toupper, OSSL_NELEM(case_change));
    ADD_ALL_TESTS(test_ctype_tolower, OSSL_NELEM(case_change));
    ADD_TEST(test_ctype_eof);
    return 1;
}