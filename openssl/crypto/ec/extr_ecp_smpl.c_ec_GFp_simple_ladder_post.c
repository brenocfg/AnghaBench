#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
struct TYPE_38__ {TYPE_1__* meth; int /*<<< orphan*/  field; int /*<<< orphan*/ * a; int /*<<< orphan*/ * b; } ;
struct TYPE_37__ {int /*<<< orphan*/ * Y; int /*<<< orphan*/ * Z; int /*<<< orphan*/ * X; } ;
struct TYPE_36__ {int /*<<< orphan*/  (* field_mul ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_POINT ;
typedef  TYPE_3__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_add_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_lshift1_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_sub_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_invert (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int EC_POINT_set_to_infinity (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub13 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub14 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub15 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub17 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub18 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub19 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub20 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub21 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub22 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub23 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub24 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_ladder_post(const EC_GROUP *group,
                              EC_POINT *r, EC_POINT *s,
                              EC_POINT *p, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *t0, *t1, *t2, *t3, *t4, *t5, *t6 = NULL;

    if (BN_is_zero(r->Z))
        return EC_POINT_set_to_infinity(group, r);

    if (BN_is_zero(s->Z)) {
        /* (X,Y,Z) -> (XZ,YZ**2,Z) */
        if (!group->meth->field_mul(group, r->X, p->X, p->Z, ctx)
            || !group->meth->field_sqr(group, r->Z, p->Z, ctx)
            || !group->meth->field_mul(group, r->Y, p->Y, r->Z, ctx)
            || !BN_copy(r->Z, p->Z)
            || !EC_POINT_invert(group, r, ctx))
            return 0;
        return 1;
    }

    BN_CTX_start(ctx);
    t0 = BN_CTX_get(ctx);
    t1 = BN_CTX_get(ctx);
    t2 = BN_CTX_get(ctx);
    t3 = BN_CTX_get(ctx);
    t4 = BN_CTX_get(ctx);
    t5 = BN_CTX_get(ctx);
    t6 = BN_CTX_get(ctx);

    if (t6 == NULL
        || !BN_mod_lshift1_quick(t0, p->Y, group->field)
        || !group->meth->field_mul(group, t1, r->X, p->Z, ctx)
        || !group->meth->field_mul(group, t2, r->Z, s->Z, ctx)
        || !group->meth->field_mul(group, t2, t1, t2, ctx)
        || !group->meth->field_mul(group, t3, t2, t0, ctx)
        || !group->meth->field_mul(group, t2, r->Z, p->Z, ctx)
        || !group->meth->field_sqr(group, t4, t2, ctx)
        || !BN_mod_lshift1_quick(t5, group->b, group->field)
        || !group->meth->field_mul(group, t4, t4, t5, ctx)
        || !group->meth->field_mul(group, t6, t2, group->a, ctx)
        || !group->meth->field_mul(group, t5, r->X, p->X, ctx)
        || !BN_mod_add_quick(t5, t6, t5, group->field)
        || !group->meth->field_mul(group, t6, r->Z, p->X, ctx)
        || !BN_mod_add_quick(t2, t6, t1, group->field)
        || !group->meth->field_mul(group, t5, t5, t2, ctx)
        || !BN_mod_sub_quick(t6, t6, t1, group->field)
        || !group->meth->field_sqr(group, t6, t6, ctx)
        || !group->meth->field_mul(group, t6, t6, s->X, ctx)
        || !BN_mod_add_quick(t4, t5, t4, group->field)
        || !group->meth->field_mul(group, t4, t4, s->Z, ctx)
        || !BN_mod_sub_quick(t4, t4, t6, group->field)
        || !group->meth->field_sqr(group, t5, r->Z, ctx)
        || !group->meth->field_mul(group, r->Z, p->Z, s->Z, ctx)
        || !group->meth->field_mul(group, r->Z, t5, r->Z, ctx)
        || !group->meth->field_mul(group, r->Z, r->Z, t0, ctx)
        /* t3 := X, t4 := Y */
        /* (X,Y,Z) -> (XZ,YZ**2,Z) */
        || !group->meth->field_mul(group, r->X, t3, r->Z, ctx)
        || !group->meth->field_sqr(group, t3, r->Z, ctx)
        || !group->meth->field_mul(group, r->Y, t4, t3, ctx))
        goto err;

    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}