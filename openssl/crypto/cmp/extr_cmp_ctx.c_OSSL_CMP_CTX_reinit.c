#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int status; int failInfoCode; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSSL_CMP_CTX_set1_senderNonce (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ OSSL_CMP_CTX_set1_transactionID (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_cmp_ctx_set0_newCert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_cmp_ctx_set0_statusString (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_cmp_ctx_set0_validatedSrvCert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_cmp_ctx_set1_caPubs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_cmp_ctx_set1_extraCertsIn (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_cmp_ctx_set1_recipNonce (TYPE_1__*,int /*<<< orphan*/ *) ; 

int OSSL_CMP_CTX_reinit(OSSL_CMP_CTX *ctx)
{
    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    ctx->status = -1;
    ctx->failInfoCode = -1;

    return ossl_cmp_ctx_set0_statusString(ctx, NULL)
        && ossl_cmp_ctx_set0_newCert(ctx, NULL)
        && ossl_cmp_ctx_set1_caPubs(ctx, NULL)
        && ossl_cmp_ctx_set1_extraCertsIn(ctx, NULL)
        && ossl_cmp_ctx_set0_validatedSrvCert(ctx, NULL)
        && OSSL_CMP_CTX_set1_transactionID(ctx, NULL)
        && OSSL_CMP_CTX_set1_senderNonce(ctx, NULL)
        && ossl_cmp_ctx_set1_recipNonce(ctx, NULL);
}