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
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_abs_is_word (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_fail_bignum_message (int /*<<< orphan*/ *,char const*,int,char*,char const*,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int test_BN_abs_eq_word(const char *file, int line, const char *bns,
                        const char *ws, const BIGNUM *a, BN_ULONG w)
{
    BIGNUM *bw, *aa;

    if (a != NULL && BN_abs_is_word(a, w))
        return 1;
    bw = BN_new();
    aa = BN_dup(a);
    BN_set_negative(aa, 0);
    BN_set_word(bw, w);
    test_fail_bignum_message(NULL, file, line, "BIGNUM", bns, ws, "abs==",
                             aa, bw);
    BN_free(bw);
    BN_free(aa);
    return 0;
}