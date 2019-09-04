#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  (* ctr128_f ) (unsigned char const*,unsigned char*,size_t,void*,scalar_t__) ;
struct TYPE_11__ {int* c; } ;
struct TYPE_10__ {int* c; } ;
struct TYPE_9__ {unsigned int* d; scalar_t__ c; } ;
struct TYPE_8__ {size_t* u; } ;
struct TYPE_12__ {unsigned int mres; TYPE_4__ EKi; TYPE_3__ Xi; TYPE_2__ Yi; int /*<<< orphan*/  (* block ) (scalar_t__,int*,void*) ;scalar_t__ ares; TYPE_1__ len; void* key; } ;
typedef  TYPE_5__ GCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  GCM_MUL (TYPE_5__*) ; 
 unsigned int GETU32 (scalar_t__) ; 
 int /*<<< orphan*/  PUTU32 (scalar_t__,unsigned int) ; 
 int U64 (int) ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,size_t,void*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int*,void*) ; 

int CRYPTO_gcm128_encrypt_ctr32(GCM128_CONTEXT *ctx,
                                const unsigned char *in, unsigned char *out,
                                size_t len, ctr128_f stream)
{
#if defined(OPENSSL_SMALL_FOOTPRINT)
    return CRYPTO_gcm128_encrypt(ctx, in, out, len);
#else
    const union {
        long one;
        char little;
    } is_endian = { 1 };
    unsigned int n, ctr, mres;
    size_t i;
    u64 mlen = ctx->len.u[1];
    void *key = ctx->key;
# ifdef GCM_FUNCREF_4BIT
    void (*gcm_gmult_p) (u64 Xi[2], const u128 Htable[16]) = ctx->gmult;
#  ifdef GHASH
    void (*gcm_ghash_p) (u64 Xi[2], const u128 Htable[16],
                         const u8 *inp, size_t len) = ctx->ghash;
#  endif
# endif

    mlen += len;
    if (mlen > ((U64(1) << 36) - 32) || (sizeof(len) == 8 && mlen < len))
        return -1;
    ctx->len.u[1] = mlen;

    mres = ctx->mres;

    if (ctx->ares) {
        /* First call to encrypt finalizes GHASH(AAD) */
#if defined(GHASH)
        if (len == 0) {
            GCM_MUL(ctx);
            ctx->ares = 0;
            return 0;
        }
        memcpy(ctx->Xn, ctx->Xi.c, sizeof(ctx->Xi));
        ctx->Xi.u[0] = 0;
        ctx->Xi.u[1] = 0;
        mres = sizeof(ctx->Xi);
#else
        GCM_MUL(ctx);
#endif
        ctx->ares = 0;
    }

    if (is_endian.little)
# ifdef BSWAP4
        ctr = BSWAP4(ctx->Yi.d[3]);
# else
        ctr = GETU32(ctx->Yi.c + 12);
# endif
    else
        ctr = ctx->Yi.d[3];

    n = mres % 16;
    if (n) {
# if defined(GHASH)
        while (n && len) {
            ctx->Xn[mres++] = *(out++) = *(in++) ^ ctx->EKi.c[n];
            --len;
            n = (n + 1) % 16;
        }
        if (n == 0) {
            GHASH(ctx, ctx->Xn, mres);
            mres = 0;
        } else {
            ctx->mres = mres;
            return 0;
        }
# else
        while (n && len) {
            ctx->Xi.c[n] ^= *(out++) = *(in++) ^ ctx->EKi.c[n];
            --len;
            n = (n + 1) % 16;
        }
        if (n == 0) {
            GCM_MUL(ctx);
            mres = 0;
        } else {
            ctx->mres = n;
            return 0;
        }
# endif
    }
# if defined(GHASH)
        if (len >= 16 && mres) {
            GHASH(ctx, ctx->Xn, mres);
            mres = 0;
        }
#  if defined(GHASH_CHUNK)
    while (len >= GHASH_CHUNK) {
        (*stream) (in, out, GHASH_CHUNK / 16, key, ctx->Yi.c);
        ctr += GHASH_CHUNK / 16;
        if (is_endian.little)
#   ifdef BSWAP4
            ctx->Yi.d[3] = BSWAP4(ctr);
#   else
            PUTU32(ctx->Yi.c + 12, ctr);
#   endif
        else
            ctx->Yi.d[3] = ctr;
        GHASH(ctx, out, GHASH_CHUNK);
        out += GHASH_CHUNK;
        in += GHASH_CHUNK;
        len -= GHASH_CHUNK;
    }
#  endif
# endif
    if ((i = (len & (size_t)-16))) {
        size_t j = i / 16;

        (*stream) (in, out, j, key, ctx->Yi.c);
        ctr += (unsigned int)j;
        if (is_endian.little)
# ifdef BSWAP4
            ctx->Yi.d[3] = BSWAP4(ctr);
# else
            PUTU32(ctx->Yi.c + 12, ctr);
# endif
        else
            ctx->Yi.d[3] = ctr;
        in += i;
        len -= i;
# if defined(GHASH)
        GHASH(ctx, out, i);
        out += i;
# else
        while (j--) {
            for (i = 0; i < 16; ++i)
                ctx->Xi.c[i] ^= out[i];
            GCM_MUL(ctx);
            out += 16;
        }
# endif
    }
    if (len) {
        (*ctx->block) (ctx->Yi.c, ctx->EKi.c, key);
        ++ctr;
        if (is_endian.little)
# ifdef BSWAP4
            ctx->Yi.d[3] = BSWAP4(ctr);
# else
            PUTU32(ctx->Yi.c + 12, ctr);
# endif
        else
            ctx->Yi.d[3] = ctr;
        while (len--) {
# if defined(GHASH)
            ctx->Xn[mres++] = out[n] = in[n] ^ ctx->EKi.c[n];
# else
            ctx->Xi.c[mres++] ^= out[n] = in[n] ^ ctx->EKi.c[n];
# endif
            ++n;
        }
    }

    ctx->mres = mres;
    return 0;
#endif
}