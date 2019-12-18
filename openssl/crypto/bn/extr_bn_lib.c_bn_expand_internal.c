#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int top; int /*<<< orphan*/  d; } ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int /*<<< orphan*/  BN_FLG_SECURE ; 
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 int /*<<< orphan*/  BN_F_BN_EXPAND_INTERNAL ; 
 int /*<<< orphan*/  BN_R_BIGNUM_TOO_LONG ; 
 int /*<<< orphan*/  BN_R_EXPAND_ON_STATIC_BIGNUM_DATA ; 
 scalar_t__ BN_get_flags (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int INT_MAX ; 
 int /*<<< orphan*/ * OPENSSL_secure_zalloc (int) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BN_ULONG *bn_expand_internal(const BIGNUM *b, int words)
{
    BN_ULONG *a = NULL;

    if (words > (INT_MAX / (4 * BN_BITS2))) {
        BNerr(BN_F_BN_EXPAND_INTERNAL, BN_R_BIGNUM_TOO_LONG);
        return NULL;
    }
    if (BN_get_flags(b, BN_FLG_STATIC_DATA)) {
        BNerr(BN_F_BN_EXPAND_INTERNAL, BN_R_EXPAND_ON_STATIC_BIGNUM_DATA);
        return NULL;
    }
    if (BN_get_flags(b, BN_FLG_SECURE))
        a = OPENSSL_secure_zalloc(words * sizeof(*a));
    else
        a = OPENSSL_zalloc(words * sizeof(*a));
    if (a == NULL) {
        BNerr(BN_F_BN_EXPAND_INTERNAL, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    assert(b->top <= words);
    if (b->top > 0)
        memcpy(a, b->d, sizeof(*a) * b->top);

    return a;
}