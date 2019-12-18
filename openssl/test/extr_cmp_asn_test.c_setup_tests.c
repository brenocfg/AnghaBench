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
 int /*<<< orphan*/  OSSL_CMP_TRANSACTIONID_LENGTH ; 
 int /*<<< orphan*/  RAND_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_data ; 
 int /*<<< orphan*/  test_ASN1_OCTET_STRING_set ; 
 int /*<<< orphan*/  test_ASN1_OCTET_STRING_set_tgt_is_src ; 
 int /*<<< orphan*/  test_cmp_asn1_get_int ; 

int setup_tests(void)
{
    RAND_bytes(rand_data, OSSL_CMP_TRANSACTIONID_LENGTH);
    /* ASN.1 related tests */
    ADD_TEST(test_cmp_asn1_get_int);
    ADD_TEST(test_ASN1_OCTET_STRING_set);
    ADD_TEST(test_ASN1_OCTET_STRING_set_tgt_is_src);
    /* TODO make sure that total number of tests (here currently 24) is shown,
     also for other cmp_*text.c. Currently the test drivers always show 1. */

    return 1;
}