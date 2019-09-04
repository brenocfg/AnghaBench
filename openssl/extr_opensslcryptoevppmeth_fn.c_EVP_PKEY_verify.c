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
struct TYPE_6__ {scalar_t__ operation; TYPE_1__* pmeth; } ;
struct TYPE_5__ {int (* verify ) (TYPE_2__*,unsigned char const*,size_t,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_VERIFY ; 
 scalar_t__ EVP_PKEY_OP_VERIFY ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVP_R_OPERATON_NOT_INITIALIZED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,unsigned char const*,size_t,unsigned char const*,size_t) ; 

int EVP_PKEY_verify(EVP_PKEY_CTX *ctx,
                    const unsigned char *sig, size_t siglen,
                    const unsigned char *tbs, size_t tbslen)
{
    if (!ctx || !ctx->pmeth || !ctx->pmeth->verify) {
        EVPerr(EVP_F_EVP_PKEY_VERIFY,
               EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }
    if (ctx->operation != EVP_PKEY_OP_VERIFY) {
        EVPerr(EVP_F_EVP_PKEY_VERIFY, EVP_R_OPERATON_NOT_INITIALIZED);
        return -1;
    }
    return ctx->pmeth->verify(ctx, sig, siglen, tbs, tbslen);
}