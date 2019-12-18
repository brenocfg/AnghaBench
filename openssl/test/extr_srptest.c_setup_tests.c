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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_srp_kat ; 
 int /*<<< orphan*/  run_srp_tests ; 

int setup_tests(void)
{
#ifdef OPENSSL_NO_SRP
    printf("No SRP support\n");
#else
    ADD_TEST(run_srp_tests);
    ADD_TEST(run_srp_kat);
#endif
    return 1;
}