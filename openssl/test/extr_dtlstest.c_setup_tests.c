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
 int /*<<< orphan*/  NUM_TESTS ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOTAL_RECORDS ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  test_cookie ; 
 int /*<<< orphan*/  test_dtls_drop_records ; 
 int /*<<< orphan*/  test_dtls_duplicate_records ; 
 int /*<<< orphan*/  test_dtls_unprocessed ; 
 int /*<<< orphan*/  test_get_argument (int) ; 

int setup_tests(void)
{
    if (!TEST_ptr(cert = test_get_argument(0))
            || !TEST_ptr(privkey = test_get_argument(1)))
        return 0;

    ADD_ALL_TESTS(test_dtls_unprocessed, NUM_TESTS);
    ADD_ALL_TESTS(test_dtls_drop_records, TOTAL_RECORDS);
    ADD_TEST(test_cookie);
    ADD_TEST(test_dtls_duplicate_records);

    return 1;
}