#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* pctx; } ;
struct TYPE_9__ {TYPE_1__* pmeth; } ;
struct TYPE_8__ {int (* digestverify ) (TYPE_3__*,unsigned char const*,size_t,unsigned char const*,size_t) ;} ;
typedef  TYPE_3__ EVP_MD_CTX ;

/* Variables and functions */
 int EVP_DigestVerifyFinal (TYPE_3__*,unsigned char const*,size_t) ; 
 scalar_t__ EVP_DigestVerifyUpdate (TYPE_3__*,unsigned char const*,size_t) ; 
 int stub1 (TYPE_3__*,unsigned char const*,size_t,unsigned char const*,size_t) ; 

int EVP_DigestVerify(EVP_MD_CTX *ctx, const unsigned char *sigret,
                     size_t siglen, const unsigned char *tbs, size_t tbslen)
{
    if (ctx->pctx->pmeth->digestverify != NULL)
        return ctx->pctx->pmeth->digestverify(ctx, sigret, siglen, tbs, tbslen);
    if (EVP_DigestVerifyUpdate(ctx, tbs, tbslen) <= 0)
        return -1;
    return EVP_DigestVerifyFinal(ctx, sigret, siglen);
}