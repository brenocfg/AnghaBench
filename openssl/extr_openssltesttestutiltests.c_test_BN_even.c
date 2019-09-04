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
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_fail_bignum_mono_message (int /*<<< orphan*/ *,char const*,int,char*,char*,char*,char const*,int /*<<< orphan*/  const*) ; 

int test_BN_even(const char *file, int line, const char *s, const BIGNUM *a)
{
    if (a != NULL && !BN_is_odd(a))
        return 1;
    test_fail_bignum_mono_message(NULL, file, line, "BIGNUM", "EVEN(", ")", s,
                                  a);
    return 0;
}