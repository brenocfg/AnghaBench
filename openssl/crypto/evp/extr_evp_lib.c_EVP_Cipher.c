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
struct TYPE_7__ {TYPE_1__* cipher; int /*<<< orphan*/  provctx; } ;
struct TYPE_6__ {int (* cupdate ) (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned int,unsigned char const*,size_t) ;int (* cfinal ) (int /*<<< orphan*/ ,unsigned char*,size_t*,size_t) ;int (* do_cipher ) (TYPE_2__*,unsigned char*,unsigned char const*,unsigned int) ;scalar_t__ (* ccipher ) (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned int,unsigned char const*,size_t) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 size_t EVP_CIPHER_CTX_block_size (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned int,unsigned char const*,size_t) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned int,unsigned char const*,size_t) ; 
 int stub3 (int /*<<< orphan*/ ,unsigned char*,size_t*,size_t) ; 
 int stub4 (TYPE_2__*,unsigned char*,unsigned char const*,unsigned int) ; 

int EVP_Cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
               const unsigned char *in, unsigned int inl)
{
    if (ctx->cipher->prov != NULL) {
        /*
         * If the provided implementation has a ccipher function, we use it,
         * and translate its return value like this: 0 => -1, 1 => outlen
         *
         * Otherwise, we call the cupdate function if in != NULL, or cfinal
         * if in == NULL.  Regardless of which, we return what we got.
         */
        int ret = -1;
        size_t outl = 0;
        size_t blocksize = EVP_CIPHER_CTX_block_size(ctx);

        if (ctx->cipher->ccipher != NULL)
            ret =  ctx->cipher->ccipher(ctx->provctx, out, &outl,
                                        inl + (blocksize == 1 ? 0 : blocksize),
                                        in, (size_t)inl)
                ? (int)outl : -1;
        else if (in != NULL)
            ret = ctx->cipher->cupdate(ctx->provctx, out, &outl,
                                       inl + (blocksize == 1 ? 0 : blocksize),
                                       in, (size_t)inl);
        else
            ret = ctx->cipher->cfinal(ctx->provctx, out, &outl,
                                      blocksize == 1 ? 0 : blocksize);

        return ret;
    }

    return ctx->cipher->do_cipher(ctx, out, in, inl);
}