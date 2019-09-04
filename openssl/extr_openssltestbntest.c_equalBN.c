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
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 

__attribute__((used)) static int equalBN(const char *op, const BIGNUM *expected, const BIGNUM *actual)
{
    if (BN_cmp(expected, actual) == 0)
        return 1;

    TEST_error("unexpected %s value", op);
    TEST_BN_eq(expected, actual);
    return 0;
}