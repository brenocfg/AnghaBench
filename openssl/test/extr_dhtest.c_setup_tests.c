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
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*) ; 
 int /*<<< orphan*/  dh_test ; 
 int /*<<< orphan*/  rfc5114_test ; 
 int /*<<< orphan*/  rfc7919_test ; 

int setup_tests(void)
{
#ifdef OPENSSL_NO_DH
    TEST_note("No DH support");
#else
    ADD_TEST(dh_test);
    ADD_TEST(rfc5114_test);
    ADD_TEST(rfc7919_test);
#endif
    return 1;
}