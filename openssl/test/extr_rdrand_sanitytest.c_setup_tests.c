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
 int /*<<< orphan*/  OPENSSL_cpuid_setup () ; 
 int* OPENSSL_ia32cap_P ; 
 int /*<<< orphan*/  sanity_check_rdrand_bytes ; 
 int /*<<< orphan*/  sanity_check_rdseed_bytes ; 

int setup_tests(void)
{
    OPENSSL_cpuid_setup();

    int have_rdseed = (OPENSSL_ia32cap_P[2] & (1 << 18)) != 0;
    int have_rdrand = (OPENSSL_ia32cap_P[1] & (1 << (62 - 32))) != 0;

    if (have_rdrand) {
        ADD_TEST(sanity_check_rdrand_bytes);
    }

    if (have_rdseed) {
        ADD_TEST(sanity_check_rdseed_bytes);
    }

    return 1;
}