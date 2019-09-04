#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* pkey; TYPE_3__* data; } ;
struct TYPE_10__ {scalar_t__ pad_mode; unsigned char* tbuf; scalar_t__ md; } ;
struct TYPE_8__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_9__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ RSA_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY_CTX ;

/* Variables and functions */
 int EVP_MD_size (scalar_t__) ; 
 int /*<<< orphan*/  EVP_MD_type (scalar_t__) ; 
 int /*<<< orphan*/  RSA_F_PKEY_RSA_VERIFYRECOVER ; 
 scalar_t__ RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_R_ALGORITHM_MISMATCH ; 
 int /*<<< orphan*/  RSA_R_INVALID_DIGEST_LENGTH ; 
 scalar_t__ RSA_X931_PADDING ; 
 scalar_t__ RSA_X931_hash_id (int /*<<< orphan*/ ) ; 
 int RSA_public_decrypt (size_t,unsigned char const*,unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int int_rsa_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  setup_tbuf (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int pkey_rsa_verifyrecover(EVP_PKEY_CTX *ctx,
                                  unsigned char *rout, size_t *routlen,
                                  const unsigned char *sig, size_t siglen)
{
    int ret;
    RSA_PKEY_CTX *rctx = ctx->data;

    if (rctx->md) {
        if (rctx->pad_mode == RSA_X931_PADDING) {
            if (!setup_tbuf(rctx, ctx))
                return -1;
            ret = RSA_public_decrypt(siglen, sig,
                                     rctx->tbuf, ctx->pkey->pkey.rsa,
                                     RSA_X931_PADDING);
            if (ret < 1)
                return 0;
            ret--;
            if (rctx->tbuf[ret] != RSA_X931_hash_id(EVP_MD_type(rctx->md))) {
                RSAerr(RSA_F_PKEY_RSA_VERIFYRECOVER,
                       RSA_R_ALGORITHM_MISMATCH);
                return 0;
            }
            if (ret != EVP_MD_size(rctx->md)) {
                RSAerr(RSA_F_PKEY_RSA_VERIFYRECOVER,
                       RSA_R_INVALID_DIGEST_LENGTH);
                return 0;
            }
            if (rout)
                memcpy(rout, rctx->tbuf, ret);
        } else if (rctx->pad_mode == RSA_PKCS1_PADDING) {
            size_t sltmp;
            ret = int_rsa_verify(EVP_MD_type(rctx->md),
                                 NULL, 0, rout, &sltmp,
                                 sig, siglen, ctx->pkey->pkey.rsa);
            if (ret <= 0)
                return 0;
            ret = sltmp;
        } else {
            return -1;
        }
    } else {
        ret = RSA_public_decrypt(siglen, sig, rout, ctx->pkey->pkey.rsa,
                                 rctx->pad_mode);
    }
    if (ret < 0)
        return ret;
    *routlen = ret;
    return 1;
}