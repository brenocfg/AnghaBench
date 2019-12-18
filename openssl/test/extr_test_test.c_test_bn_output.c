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
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** bn_output_tests ; 
 int /*<<< orphan*/  test_output_bignum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_bn_output(int n)
{
    BIGNUM *b = NULL;

    if (bn_output_tests[n] != NULL
            && !TEST_true(BN_hex2bn(&b, bn_output_tests[n])))
        return 0;
    test_output_bignum(bn_output_tests[n], b);
    BN_free(b);
    return 1;
}