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
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int TEST_BN_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_bn(const char *name, const BIGNUM *bn, const char *hexbn)
{
    BIGNUM *tmp = NULL;
    int r;

    if (!TEST_true(BN_hex2bn(&tmp, hexbn)))
        return 0;

    if (BN_cmp(bn, tmp) != 0)
        TEST_error("unexpected %s value", name);
    r = TEST_BN_eq(bn, tmp);
    BN_free(tmp);
    return r;
}