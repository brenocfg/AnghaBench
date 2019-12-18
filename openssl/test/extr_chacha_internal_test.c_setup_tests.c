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
typedef  int /*<<< orphan*/  ref ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OPENSSL_cpuid_setup () ; 
 int /*<<< orphan*/  test_cha_cha_internal ; 

int setup_tests(void)
{
#ifdef CPUID_OBJ
    OPENSSL_cpuid_setup();
#endif

    ADD_ALL_TESTS(test_cha_cha_internal, sizeof(ref));
    return 1;
}