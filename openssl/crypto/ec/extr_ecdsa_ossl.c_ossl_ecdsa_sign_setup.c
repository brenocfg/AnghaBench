#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* group; } ;
struct TYPE_7__ {TYPE_1__* meth; } ;
struct TYPE_6__ {int (* ecdsa_sign_setup ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_3__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_OSSL_ECDSA_SIGN_SETUP ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_ECDSA ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int ossl_ecdsa_sign_setup(EC_KEY *eckey, BN_CTX *ctx_in, BIGNUM **kinvp,
                          BIGNUM **rp)
{
    if (eckey->group->meth->ecdsa_sign_setup == NULL) {
        ECerr(EC_F_OSSL_ECDSA_SIGN_SETUP, EC_R_CURVE_DOES_NOT_SUPPORT_ECDSA);
        return 0;
    }

    return eckey->group->meth->ecdsa_sign_setup(eckey, ctx_in, kinvp, rp);
}