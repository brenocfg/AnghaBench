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
 int /*<<< orphan*/  test_PKISI ; 

int setup_tests(void)
{
    /*-
     * this tests all of:
     * ossl_cmp_statusinfo_new()
     * ossl_cmp_pkisi_get_pkistatus()
     * ossl_cmp_PKIStatus_to_string()
     * ossl_cmp_pkisi_get0_statusstring()
     * ossl_cmp_pkisi_get_pkifailureinfo()
     * ossl_cmp_pkisi_pkifailureinfo_check()
     */
    ADD_TEST(test_PKISI);
    return 1;
}