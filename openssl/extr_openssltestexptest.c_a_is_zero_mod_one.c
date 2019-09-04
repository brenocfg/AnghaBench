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
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_print_var (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 

__attribute__((used)) static int a_is_zero_mod_one(const char *method, const BIGNUM *r,
                             const BIGNUM *a)
{
    if (!BN_is_zero(r)) {
        TEST_error("%s failed: a ** 0 mod 1 = r (should be 0)", method);
        BN_print_var(a);
        BN_print_var(r);
        return 0;
    }
    return 1;
}