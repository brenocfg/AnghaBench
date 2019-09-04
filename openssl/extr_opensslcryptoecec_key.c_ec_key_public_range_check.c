#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  field; int /*<<< orphan*/  meth; } ;
struct TYPE_5__ {TYPE_3__* group; int /*<<< orphan*/  pub_key; } ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_degree (TYPE_3__*) ; 
 scalar_t__ EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NID_X9_62_prime_field ; 

__attribute__((used)) static int ec_key_public_range_check(BN_CTX *ctx, const EC_KEY *key)
{
    int ret = 0;
    BIGNUM *x, *y;

    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (y == NULL)
        goto err;

    if (!EC_POINT_get_affine_coordinates(key->group, key->pub_key, x, y, ctx))
        goto err;

    if (EC_METHOD_get_field_type(key->group->meth) == NID_X9_62_prime_field) {
        if (BN_is_negative(x)
            || BN_cmp(x, key->group->field) >= 0
            || BN_is_negative(y)
            || BN_cmp(y, key->group->field) >= 0) {
            goto err;
        }
    } else {
        int m = EC_GROUP_get_degree(key->group);
        if (BN_num_bits(x) > m || BN_num_bits(y) > m) {
            goto err;
        }
    }
    ret = 1;
err:
    BN_CTX_end(ctx);
    return ret;
}