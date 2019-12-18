#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * md; } ;
struct TYPE_8__ {TYPE_2__* pkey; TYPE_4__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dsa; } ;
struct TYPE_7__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  TYPE_4__ DSA_PKEY_CTX ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int DSA_sign (int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_MD_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_dsa_sign(EVP_PKEY_CTX *ctx, unsigned char *sig,
                         size_t *siglen, const unsigned char *tbs,
                         size_t tbslen)
{
    int ret;
    unsigned int sltmp;
    DSA_PKEY_CTX *dctx = ctx->data;
    DSA *dsa = ctx->pkey->pkey.dsa;

    if (dctx->md != NULL && tbslen != (size_t)EVP_MD_size(dctx->md))
        return 0;

    ret = DSA_sign(0, tbs, tbslen, sig, &sltmp, dsa);

    if (ret <= 0)
        return ret;
    *siglen = sltmp;
    return 1;
}