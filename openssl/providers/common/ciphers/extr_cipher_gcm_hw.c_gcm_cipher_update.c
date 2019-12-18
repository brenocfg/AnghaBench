#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t* u; } ;
struct TYPE_12__ {int /*<<< orphan*/  u; } ;
struct TYPE_11__ {int /*<<< orphan*/  c; } ;
struct TYPE_15__ {int mres; TYPE_3__ len; TYPE_2__ Xi; TYPE_1__ Yi; int /*<<< orphan*/  key; } ;
struct TYPE_14__ {TYPE_6__ gcm; int /*<<< orphan*/ * ctr; scalar_t__ enc; } ;
typedef  TYPE_4__ PROV_GCM_CTX ;

/* Variables and functions */
 scalar_t__ AES_GCM_ASM (TYPE_4__*) ; 
 scalar_t__ CRYPTO_gcm128_decrypt (TYPE_6__*,unsigned char const*,unsigned char*,size_t) ; 
 scalar_t__ CRYPTO_gcm128_decrypt_ctr32 (TYPE_6__*,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ CRYPTO_gcm128_encrypt (TYPE_6__*,unsigned char const*,unsigned char*,size_t) ; 
 scalar_t__ CRYPTO_gcm128_encrypt_ctr32 (TYPE_6__*,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 size_t aesni_gcm_decrypt (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t aesni_gcm_encrypt (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gcm_cipher_update(PROV_GCM_CTX *ctx, const unsigned char *in,
                      size_t len, unsigned char *out)
{
    if (ctx->enc) {
        if (ctx->ctr != NULL) {
#if defined(AES_GCM_ASM)
            size_t bulk = 0;

            if (len >= 32 && AES_GCM_ASM(ctx)) {
                size_t res = (16 - ctx->gcm.mres) % 16;

                if (CRYPTO_gcm128_encrypt(&ctx->gcm, in, out, res))
                    return 0;
                bulk = aesni_gcm_encrypt(in + res, out + res, len - res,
                                         ctx->gcm.key,
                                         ctx->gcm.Yi.c, ctx->gcm.Xi.u);
                ctx->gcm.len.u[1] += bulk;
                bulk += res;
            }
            if (CRYPTO_gcm128_encrypt_ctr32(&ctx->gcm, in + bulk, out + bulk,
                                            len - bulk, ctx->ctr))
                return 0;
#else
            if (CRYPTO_gcm128_encrypt_ctr32(&ctx->gcm, in, out, len, ctx->ctr))
                return 0;
#endif /* AES_GCM_ASM */
        } else {
            if (CRYPTO_gcm128_encrypt(&ctx->gcm, in, out, len))
                return 0;
        }
    } else {
        if (ctx->ctr != NULL) {
#if defined(AES_GCM_ASM)
            size_t bulk = 0;

            if (len >= 16 && AES_GCM_ASM(ctx)) {
                size_t res = (16 - ctx->gcm.mres) % 16;

                if (CRYPTO_gcm128_decrypt(&ctx->gcm, in, out, res))
                    return -1;

                bulk = aesni_gcm_decrypt(in + res, out + res, len - res,
                                         ctx->gcm.key,
                                         ctx->gcm.Yi.c, ctx->gcm.Xi.u);
                ctx->gcm.len.u[1] += bulk;
                bulk += res;
            }
            if (CRYPTO_gcm128_decrypt_ctr32(&ctx->gcm, in + bulk, out + bulk,
                                            len - bulk, ctx->ctr))
                return 0;
#else
            if (CRYPTO_gcm128_decrypt_ctr32(&ctx->gcm, in, out, len, ctx->ctr))
                return 0;
#endif /* AES_GCM_ASM */
        } else {
            if (CRYPTO_gcm128_decrypt(&ctx->gcm, in, out, len))
                return 0;
        }
    }
    return 1;
}