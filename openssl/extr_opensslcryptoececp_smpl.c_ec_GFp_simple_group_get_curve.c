#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; TYPE_1__* meth; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* field_decode ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_group_get_curve(const EC_GROUP *group, BIGNUM *p, BIGNUM *a,
                                  BIGNUM *b, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX *new_ctx = NULL;

    if (p != NULL) {
        if (!BN_copy(p, group->field))
            return 0;
    }

    if (a != NULL || b != NULL) {
        if (group->meth->field_decode) {
            if (ctx == NULL) {
                ctx = new_ctx = BN_CTX_new();
                if (ctx == NULL)
                    return 0;
            }
            if (a != NULL) {
                if (!group->meth->field_decode(group, a, group->a, ctx))
                    goto err;
            }
            if (b != NULL) {
                if (!group->meth->field_decode(group, b, group->b, ctx))
                    goto err;
            }
        } else {
            if (a != NULL) {
                if (!BN_copy(a, group->a))
                    goto err;
            }
            if (b != NULL) {
                if (!BN_copy(b, group->b))
                    goto err;
            }
        }
    }

    ret = 1;

 err:
    BN_CTX_free(new_ctx);
    return ret;
}