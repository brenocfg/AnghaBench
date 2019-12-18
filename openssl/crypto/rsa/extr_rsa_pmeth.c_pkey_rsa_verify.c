#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* pkey; TYPE_3__* data; } ;
struct TYPE_11__ {scalar_t__ pad_mode; int /*<<< orphan*/  tbuf; int /*<<< orphan*/  saltlen; int /*<<< orphan*/  mgf1md; scalar_t__ md; } ;
struct TYPE_9__ {int /*<<< orphan*/ * rsa; } ;
struct TYPE_10__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ RSA_PKEY_CTX ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_4__ EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ EVP_MD_size (scalar_t__) ; 
 int /*<<< orphan*/  EVP_MD_type (scalar_t__) ; 
 int /*<<< orphan*/  RSA_F_PKEY_RSA_VERIFY ; 
 scalar_t__ RSA_NO_PADDING ; 
 scalar_t__ RSA_PKCS1_PADDING ; 
 scalar_t__ RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_R_INVALID_DIGEST_LENGTH ; 
 scalar_t__ RSA_X931_PADDING ; 
 void* RSA_public_decrypt (size_t,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int RSA_verify (int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int RSA_verify_PKCS1_PSS_mgf1 (int /*<<< orphan*/ *,unsigned char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ pkey_rsa_verifyrecover (TYPE_4__*,int /*<<< orphan*/ *,size_t*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  setup_tbuf (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int pkey_rsa_verify(EVP_PKEY_CTX *ctx,
                           const unsigned char *sig, size_t siglen,
                           const unsigned char *tbs, size_t tbslen)
{
    RSA_PKEY_CTX *rctx = ctx->data;
    RSA *rsa = ctx->pkey->pkey.rsa;
    size_t rslen;

    if (rctx->md) {
        if (rctx->pad_mode == RSA_PKCS1_PADDING)
            return RSA_verify(EVP_MD_type(rctx->md), tbs, tbslen,
                              sig, siglen, rsa);
        if (tbslen != (size_t)EVP_MD_size(rctx->md)) {
            RSAerr(RSA_F_PKEY_RSA_VERIFY, RSA_R_INVALID_DIGEST_LENGTH);
            return -1;
        }
        if (rctx->pad_mode == RSA_X931_PADDING) {
            if (pkey_rsa_verifyrecover(ctx, NULL, &rslen, sig, siglen) <= 0)
                return 0;
        } else if (rctx->pad_mode == RSA_PKCS1_PSS_PADDING) {
            int ret;
            if (!setup_tbuf(rctx, ctx))
                return -1;
            ret = RSA_public_decrypt(siglen, sig, rctx->tbuf,
                                     rsa, RSA_NO_PADDING);
            if (ret <= 0)
                return 0;
            ret = RSA_verify_PKCS1_PSS_mgf1(rsa, tbs,
                                            rctx->md, rctx->mgf1md,
                                            rctx->tbuf, rctx->saltlen);
            if (ret <= 0)
                return 0;
            return 1;
        } else {
            return -1;
        }
    } else {
        if (!setup_tbuf(rctx, ctx))
            return -1;
        rslen = RSA_public_decrypt(siglen, sig, rctx->tbuf,
                                   rsa, rctx->pad_mode);
        if (rslen == 0)
            return 0;
    }

    if ((rslen != tbslen) || memcmp(tbs, rctx->tbuf, rslen))
        return 0;

    return 1;

}