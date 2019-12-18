#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int buf_len; int flags; int* buf; TYPE_1__* cipher; int /*<<< orphan*/  provctx; int /*<<< orphan*/  encrypt; } ;
struct TYPE_7__ {int (* cfinal ) (int /*<<< orphan*/ ,unsigned char*,size_t*,int) ;int flags; int (* do_cipher ) (TYPE_2__*,unsigned char*,int*,unsigned int) ;unsigned int block_size; int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_block_size (TYPE_2__*) ; 
 int EVP_CIPH_FLAG_CUSTOM_CIPHER ; 
 int EVP_CIPH_NO_PADDING ; 
 int /*<<< orphan*/  EVP_F_EVP_ENCRYPTFINAL_EX ; 
 int /*<<< orphan*/  EVP_R_DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH ; 
 int /*<<< orphan*/  EVP_R_FINAL_ERROR ; 
 int /*<<< orphan*/  EVP_R_INVALID_OPERATION ; 
 int /*<<< orphan*/  EVP_R_NO_CIPHER_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,size_t*,int) ; 
 int stub2 (TYPE_2__*,unsigned char*,int*,unsigned int) ; 
 int stub3 (TYPE_2__*,unsigned char*,int*,unsigned int) ; 

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl)
{
    int n, ret;
    unsigned int i, b, bl;
    size_t soutl;
    int blocksize;

    /* Prevent accidental use of decryption context when encrypting */
    if (!ctx->encrypt) {
        EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX, EVP_R_INVALID_OPERATION);
        return 0;
    }

    if (ctx->cipher == NULL) {
        EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX, EVP_R_NO_CIPHER_SET);
        return 0;
    }
    if (ctx->cipher->prov == NULL)
        goto legacy;

    blocksize = EVP_CIPHER_CTX_block_size(ctx);

    if (blocksize < 1 || ctx->cipher->cfinal == NULL) {
        EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX, EVP_R_FINAL_ERROR);
        return 0;
    }

    ret = ctx->cipher->cfinal(ctx->provctx, out, &soutl,
                              blocksize == 1 ? 0 : blocksize);

    if (ret) {
        if (soutl > INT_MAX) {
            EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX, EVP_R_FINAL_ERROR);
            return 0;
        }
        *outl = soutl;
    }

    return ret;

    /* TODO(3.0): Remove legacy code below */
 legacy:

    if (ctx->cipher->flags & EVP_CIPH_FLAG_CUSTOM_CIPHER) {
        ret = ctx->cipher->do_cipher(ctx, out, NULL, 0);
        if (ret < 0)
            return 0;
        else
            *outl = ret;
        return 1;
    }

    b = ctx->cipher->block_size;
    OPENSSL_assert(b <= sizeof(ctx->buf));
    if (b == 1) {
        *outl = 0;
        return 1;
    }
    bl = ctx->buf_len;
    if (ctx->flags & EVP_CIPH_NO_PADDING) {
        if (bl) {
            EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX,
                   EVP_R_DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH);
            return 0;
        }
        *outl = 0;
        return 1;
    }

    n = b - bl;
    for (i = bl; i < b; i++)
        ctx->buf[i] = n;
    ret = ctx->cipher->do_cipher(ctx, out, ctx->buf, b);

    if (ret)
        *outl = b;

    return ret;
}