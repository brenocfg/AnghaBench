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
struct TYPE_3__ {int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/  libctx; int /*<<< orphan*/ * group; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_secure_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_range_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_set_to_infinity (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ec_key_simple_generate_key(EC_KEY *eckey)
{
    int ok = 0;
    BIGNUM *priv_key = NULL;
    const BIGNUM *order = NULL;
    EC_POINT *pub_key = NULL;
    const EC_GROUP *group = eckey->group;
    BN_CTX *ctx = BN_CTX_secure_new_ex(eckey->libctx);

    if (ctx == NULL)
        goto err;

    if (eckey->priv_key == NULL) {
        priv_key = BN_secure_new();
        if (priv_key == NULL)
            goto err;
    } else
        priv_key = eckey->priv_key;

    /*
     * Steps (1-2): Check domain parameters and security strength.
     * These steps must be done by the user. This would need to be
     * stated in the security policy.
     */

    order = EC_GROUP_get0_order(group);
    if (order == NULL)
        goto err;

    /*
     * Steps (3-7): priv_key = DRBG_RAND(order_n_bits) (range [1, n-1]).
     * Although this is slightly different from the standard, it is effectively
     * equivalent as it gives an unbiased result ranging from 1..n-1. It is also
     * faster as the standard needs to retry more often. Also doing
     * 1 + rand[0..n-2] would effect the way that tests feed dummy entropy into
     * rand so the simpler backward compatible method has been used here.
     */
    do
        if (!BN_priv_rand_range_ex(priv_key, order, ctx))
            goto err;
    while (BN_is_zero(priv_key)) ;

    if (eckey->pub_key == NULL) {
        pub_key = EC_POINT_new(group);
        if (pub_key == NULL)
            goto err;
    } else
        pub_key = eckey->pub_key;

    /* Step (8) : pub_key = priv_key * G (where G is a point on the curve) */
    if (!EC_POINT_mul(group, pub_key, priv_key, NULL, NULL, ctx))
        goto err;

    eckey->priv_key = priv_key;
    eckey->pub_key = pub_key;
    priv_key = NULL;
    pub_key = NULL;

    ok = 1;

err:
    /* Step (9): If there is an error return an invalid keypair. */
    if (!ok) {
        BN_clear(eckey->priv_key);
        if (eckey->pub_key != NULL)
            EC_POINT_set_to_infinity(group, eckey->pub_key);
    }

    EC_POINT_free(pub_key);
    BN_clear_free(priv_key);
    BN_CTX_free(ctx);
    return ok;
}