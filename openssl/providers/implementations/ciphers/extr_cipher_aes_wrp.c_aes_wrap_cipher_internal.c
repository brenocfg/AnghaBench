#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ks; } ;
struct TYPE_6__ {size_t (* wrapfn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t,int /*<<< orphan*/ ) ;TYPE_1__ ks; } ;
struct TYPE_5__ {int pad; int /*<<< orphan*/  block; int /*<<< orphan*/ * iv; scalar_t__ iv_set; scalar_t__ enc; } ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;
typedef  TYPE_3__ PROV_AES_WRAP_CTX ;

/* Variables and functions */
 size_t stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aes_wrap_cipher_internal(void *vctx, unsigned char *out,
                                    const unsigned char *in, size_t inlen)
{
    PROV_CIPHER_CTX *ctx = (PROV_CIPHER_CTX *)vctx;
    PROV_AES_WRAP_CTX *wctx = (PROV_AES_WRAP_CTX *)vctx;
    size_t rv;
    int pad = ctx->pad;

    /* No final operation so always return zero length */
    if (in == NULL)
        return 0;

    /* Input length must always be non-zero */
    if (inlen == 0)
        return -1;

    /* If decrypting need at least 16 bytes and multiple of 8 */
    if (!ctx->enc && (inlen < 16 || inlen & 0x7))
        return -1;

    /* If not padding input must be multiple of 8 */
    if (!pad && inlen & 0x7)
        return -1;

    if (out == NULL) {
        if (ctx->enc) {
            /* If padding round up to multiple of 8 */
            if (pad)
                inlen = (inlen + 7) / 8 * 8;
            /* 8 byte prefix */
            return inlen + 8;
        } else {
            /*
             * If not padding output will be exactly 8 bytes smaller than
             * input. If padding it will be at least 8 bytes smaller but we
             * don't know how much.
             */
            return inlen - 8;
        }
    }

    rv = wctx->wrapfn(&wctx->ks.ks, ctx->iv_set ? ctx->iv : NULL, out, in,
                      inlen, ctx->block);
    return rv ? (int)rv : -1;
}