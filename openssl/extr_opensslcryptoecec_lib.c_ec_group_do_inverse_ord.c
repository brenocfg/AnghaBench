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
struct TYPE_7__ {TYPE_1__* meth; } ;
struct TYPE_6__ {int (* field_inverse_mod_ord ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int ec_field_inverse_mod_ord (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ec_group_do_inverse_ord(const EC_GROUP *group, BIGNUM *res,
                            const BIGNUM *x, BN_CTX *ctx)
{
    if (group->meth->field_inverse_mod_ord != NULL)
        return group->meth->field_inverse_mod_ord(group, res, x, ctx);
    else
        return ec_field_inverse_mod_ord(group, res, x, ctx);
}