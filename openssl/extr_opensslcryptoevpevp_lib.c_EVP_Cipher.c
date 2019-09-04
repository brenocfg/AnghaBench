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
struct TYPE_6__ {int (* ccipher ) (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned int,unsigned char const*,size_t) ;int (* do_cipher ) (TYPE_2__*,unsigned char*,unsigned char const*,unsigned int) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_block_size (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned int,unsigned char const*,size_t) ; 
 int stub2 (TYPE_2__*,unsigned char*,unsigned char const*,unsigned int) ; 

int EVP_Cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
               const unsigned char *in, unsigned int inl)
{
    if (ctx->cipher->prov != NULL) {
        size_t outl = 0;         /* ignored */
        int blocksize = EVP_CIPHER_CTX_block_size(ctx);

        if (ctx->cipher->ccipher != NULL)
            return
                ctx->cipher->ccipher(ctx->provctx, out, &outl,
                                     inl + (blocksize == 1 ? 0 : blocksize),
                                     in, (size_t)inl);
        return 0;
    }

    return ctx->cipher->do_cipher(ctx, out, in, inl);
}