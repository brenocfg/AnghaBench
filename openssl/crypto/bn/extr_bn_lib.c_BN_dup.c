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
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_SECURE ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_get_flags (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 int /*<<< orphan*/  const* BN_secure_new () ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

BIGNUM *BN_dup(const BIGNUM *a)
{
    BIGNUM *t;

    if (a == NULL)
        return NULL;
    bn_check_top(a);

    t = BN_get_flags(a, BN_FLG_SECURE) ? BN_secure_new() : BN_new();
    if (t == NULL)
        return NULL;
    if (!BN_copy(t, a)) {
        BN_free(t);
        return NULL;
    }
    bn_check_top(t);
    return t;
}