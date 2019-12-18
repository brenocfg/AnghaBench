#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_1__* meth; } ;
struct TYPE_27__ {int Z_is_one; int /*<<< orphan*/ * Y; int /*<<< orphan*/ * X; int /*<<< orphan*/ * Z; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* field_mul ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_inv ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_POINT ;
typedef  TYPE_3__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_LADDER_POST ; 
 int /*<<< orphan*/  EC_POINT_copy (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  EC_POINT_invert (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int EC_POINT_set_to_infinity (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int ec_GF2m_simple_ladder_post(const EC_GROUP *group,
                               EC_POINT *r, EC_POINT *s,
                               EC_POINT *p, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *t0, *t1, *t2 = NULL;

    if (BN_is_zero(r->Z))
        return EC_POINT_set_to_infinity(group, r);

    if (BN_is_zero(s->Z)) {
        if (!EC_POINT_copy(r, p)
            || !EC_POINT_invert(group, r, ctx)) {
            ECerr(EC_F_EC_GF2M_SIMPLE_LADDER_POST, ERR_R_EC_LIB);
            return 0;
        }
        return 1;
    }

    BN_CTX_start(ctx);
    t0 = BN_CTX_get(ctx);
    t1 = BN_CTX_get(ctx);
    t2 = BN_CTX_get(ctx);
    if (t2 == NULL) {
        ECerr(EC_F_EC_GF2M_SIMPLE_LADDER_POST, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (!group->meth->field_mul(group, t0, r->Z, s->Z, ctx)
        || !group->meth->field_mul(group, t1, p->X, r->Z, ctx)
        || !BN_GF2m_add(t1, r->X, t1)
        || !group->meth->field_mul(group, t2, p->X, s->Z, ctx)
        || !group->meth->field_mul(group, r->Z, r->X, t2, ctx)
        || !BN_GF2m_add(t2, t2, s->X)
        || !group->meth->field_mul(group, t1, t1, t2, ctx)
        || !group->meth->field_sqr(group, t2, p->X, ctx)
        || !BN_GF2m_add(t2, p->Y, t2)
        || !group->meth->field_mul(group, t2, t2, t0, ctx)
        || !BN_GF2m_add(t1, t2, t1)
        || !group->meth->field_mul(group, t2, p->X, t0, ctx)
        || !group->meth->field_inv(group, t2, t2, ctx)
        || !group->meth->field_mul(group, t1, t1, t2, ctx)
        || !group->meth->field_mul(group, r->X, r->Z, t2, ctx)
        || !BN_GF2m_add(t2, p->X, r->X)
        || !group->meth->field_mul(group, t2, t2, t1, ctx)
        || !BN_GF2m_add(r->Y, p->Y, t2)
        || !BN_one(r->Z))
        goto err;

    r->Z_is_one = 1;

    /* GF(2^m) field elements should always have BIGNUM::neg = 0 */
    BN_set_negative(r->X, 0);
    BN_set_negative(r->Y, 0);

    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}