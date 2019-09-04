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
struct TYPE_9__ {scalar_t__ md; } ;
struct TYPE_8__ {TYPE_2__* pkey; TYPE_4__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_7__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  TYPE_4__ EC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int ECDSA_verify (int,unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int EVP_MD_type (scalar_t__) ; 
 int NID_sha1 ; 

__attribute__((used)) static int pkey_ec_verify(EVP_PKEY_CTX *ctx,
                          const unsigned char *sig, size_t siglen,
                          const unsigned char *tbs, size_t tbslen)
{
    int ret, type;
    EC_PKEY_CTX *dctx = ctx->data;
    EC_KEY *ec = ctx->pkey->pkey.ec;

    if (dctx->md)
        type = EVP_MD_type(dctx->md);
    else
        type = NID_sha1;

    ret = ECDSA_verify(type, tbs, tbslen, sig, siglen, ec);

    return ret;
}