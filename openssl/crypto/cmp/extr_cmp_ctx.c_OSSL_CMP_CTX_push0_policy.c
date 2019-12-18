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
struct TYPE_3__ {int /*<<< orphan*/ * policies; } ;
typedef  int /*<<< orphan*/  POLICYINFO ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * CERTIFICATEPOLICIES_new () ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sk_POLICYINFO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OSSL_CMP_CTX_push0_policy(OSSL_CMP_CTX *ctx, POLICYINFO *pinfo)
{
    if (ctx == NULL || pinfo == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    if (ctx->policies == NULL
            && (ctx->policies = CERTIFICATEPOLICIES_new()) == NULL)
        return 0;

    return sk_POLICYINFO_push(ctx->policies, pinfo);
}