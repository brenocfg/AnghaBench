#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int (* dsa_sign_setup ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_2__ DSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int DSA_sign_setup(DSA *dsa, BN_CTX *ctx_in, BIGNUM **kinvp, BIGNUM **rp)
{
    return dsa->meth->dsa_sign_setup(dsa, ctx_in, kinvp, rp);
}