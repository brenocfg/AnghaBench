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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_long_bignum(void)
{
    int r;
    BIGNUM *a = NULL, *b = NULL, *c = NULL, *d = NULL;
    const char as[] = "1234567890123456789012345678901234567890123456789012"
                      "1234567890123456789012345678901234567890123456789012"
                      "1234567890123456789012345678901234567890123456789012"
                      "1234567890123456789012345678901234567890123456789012"
                      "1234567890123456789012345678901234567890123456789012"
                      "1234567890123456789012345678901234567890123456789012"
                      "FFFFFF";
    const char bs[] = "1234567890123456789012345678901234567890123456789012"
                      "1234567890123456789012345678901234567890123456789013"
                      "987657";
    const char cs[] = "-"        /* 64 characters plus sign */
                      "123456789012345678901234567890"
                      "123456789012345678901234567890"
                      "ABCD";
    const char ds[] = "-"        /* 63 characters plus sign */
                      "23456789A123456789B123456789C"
                      "123456789D123456789E123456789F"
                      "ABCD";

    r = TEST_true(BN_hex2bn(&a, as))
        && TEST_true(BN_hex2bn(&b, bs))
        && TEST_true(BN_hex2bn(&c, cs))
        && TEST_true(BN_hex2bn(&d, ds))
        && (TEST(0, TEST_BN_eq(a, b))
            & TEST(0, TEST_BN_eq(b, a))
            & TEST(0, TEST_BN_eq(b, NULL))
            & TEST(0, TEST_BN_eq(NULL, a))
            & TEST(1, TEST_BN_ne(a, NULL))
            & TEST(0, TEST_BN_eq(c, d)));
    BN_free(a);
    BN_free(b);
    BN_free(c);
    BN_free(d);
    return r;
}