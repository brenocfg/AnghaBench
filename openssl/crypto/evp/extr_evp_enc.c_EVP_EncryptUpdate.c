#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  provctx; TYPE_1__* cipher; int /*<<< orphan*/  encrypt; } ;
struct TYPE_6__ {int (* cupdate ) (int /*<<< orphan*/ ,unsigned char*,size_t*,int,unsigned char const*,size_t) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_block_size (TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_F_EVP_ENCRYPTUPDATE ; 
 int /*<<< orphan*/  EVP_R_INVALID_OPERATION ; 
 int /*<<< orphan*/  EVP_R_NO_CIPHER_SET ; 
 int /*<<< orphan*/  EVP_R_UPDATE_ERROR ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int evp_EncryptDecryptUpdate (TYPE_2__*,unsigned char*,int*,unsigned char const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,size_t*,int,unsigned char const*,size_t) ; 

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl,
                      const unsigned char *in, int inl)
{
    int ret;
    size_t soutl;
    int blocksize;

    /* Prevent accidental use of decryption context when encrypting */
    if (!ctx->encrypt) {
        EVPerr(EVP_F_EVP_ENCRYPTUPDATE, EVP_R_INVALID_OPERATION);
        return 0;
    }

    if (ctx->cipher == NULL) {
        EVPerr(EVP_F_EVP_ENCRYPTUPDATE, EVP_R_NO_CIPHER_SET);
        return 0;
    }

    if (ctx->cipher->prov == NULL)
        goto legacy;

    blocksize = EVP_CIPHER_CTX_block_size(ctx);

    if (ctx->cipher->cupdate == NULL  || blocksize < 1) {
        EVPerr(EVP_F_EVP_ENCRYPTUPDATE, EVP_R_UPDATE_ERROR);
        return 0;
    }
    ret = ctx->cipher->cupdate(ctx->provctx, out, &soutl,
                               inl + (blocksize == 1 ? 0 : blocksize), in,
                               (size_t)inl);

    if (ret) {
        if (soutl > INT_MAX) {
            EVPerr(EVP_F_EVP_ENCRYPTUPDATE, EVP_R_UPDATE_ERROR);
            return 0;
        }
        *outl = soutl;
    }

    return ret;

    /* TODO(3.0): Remove legacy code below */
 legacy:

    return evp_EncryptDecryptUpdate(ctx, out, outl, in, inl);
}