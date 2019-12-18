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
struct TYPE_6__ {int /*<<< orphan*/ * (* ecdsa_sign_sig ) (unsigned char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_3__*) ;} ;
typedef  TYPE_3__ EC_KEY ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_OSSL_ECDSA_SIGN_SIG ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_ECDSA ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (unsigned char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_3__*) ; 

ECDSA_SIG *ossl_ecdsa_sign_sig(const unsigned char *dgst, int dgst_len,
                               const BIGNUM *in_kinv, const BIGNUM *in_r,
                               EC_KEY *eckey)
{
    if (eckey->group->meth->ecdsa_sign_sig == NULL) {
        ECerr(EC_F_OSSL_ECDSA_SIGN_SIG, EC_R_CURVE_DOES_NOT_SUPPORT_ECDSA);
        return NULL;
    }

    return eckey->group->meth->ecdsa_sign_sig(dgst, dgst_len,
                                              in_kinv, in_r, eckey);
}