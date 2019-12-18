#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p; int /*<<< orphan*/  g; } ;
typedef  TYPE_1__ DH ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/ *,int) ; 
 int DH_CHECK_P_NOT_PRIME ; 
 scalar_t__ DH_MIN_MODULUS_BITS ; 
 int DH_MODULUS_TOO_LARGE ; 
 int DH_MODULUS_TOO_SMALL ; 
 int DH_NOT_SUITABLE_GENERATOR ; 
 scalar_t__ OPENSSL_DH_MAX_MODULUS_BITS ; 

int DH_check_params(const DH *dh, int *ret)
{
    int ok = 0;
    BIGNUM *tmp = NULL;
    BN_CTX *ctx = NULL;

    *ret = 0;
    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    if (tmp == NULL)
        goto err;

    if (!BN_is_odd(dh->p))
        *ret |= DH_CHECK_P_NOT_PRIME;
    if (BN_is_negative(dh->g) || BN_is_zero(dh->g) || BN_is_one(dh->g))
        *ret |= DH_NOT_SUITABLE_GENERATOR;
    if (BN_copy(tmp, dh->p) == NULL || !BN_sub_word(tmp, 1))
        goto err;
    if (BN_cmp(dh->g, tmp) >= 0)
        *ret |= DH_NOT_SUITABLE_GENERATOR;
    if (BN_num_bits(dh->p) < DH_MIN_MODULUS_BITS)
        *ret |= DH_MODULUS_TOO_SMALL;
    if (BN_num_bits(dh->p) > OPENSSL_DH_MAX_MODULUS_BITS)
        *ret |= DH_MODULUS_TOO_LARGE;

    ok = 1;
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ok;
}