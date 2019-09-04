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
typedef  int /*<<< orphan*/  (* block128_f ) (scalar_t__,int*,void*) ;
struct TYPE_11__ {int* c; size_t const* t; } ;
struct TYPE_10__ {int* c; size_t* t; } ;
struct TYPE_9__ {unsigned int* d; scalar_t__ c; } ;
struct TYPE_8__ {size_t* u; } ;
struct TYPE_12__ {unsigned int mres; TYPE_4__ EKi; TYPE_3__ Xi; TYPE_2__ Yi; scalar_t__ ares; TYPE_1__ len; void* key; int /*<<< orphan*/  (* block ) (scalar_t__,int*,void*) ;} ;
typedef  TYPE_5__ GCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  GCM_MUL (TYPE_5__*) ; 
 unsigned int GETU32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTU32 (scalar_t__,unsigned int) ; 
 int U64 (int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int*,void*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int*,void*) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int*,void*) ; 

int CRYPTO_gcm128_encrypt(GCM128_CONTEXT *ctx,
                          const unsigned char *in, unsigned char *out,
                          size_t len)
{
    const union {
        long one;
        char little;
    } is_endian = { 1 };
    unsigned int n, ctr, mres;
    size_t i;
    u64 mlen = ctx->len.u[1];
    block128_f block = ctx->block;
    void *key = ctx->key;
#ifdef GCM_FUNCREF_4BIT
    void (*gcm_gmult_p) (u64 Xi[2], const u128 Htable[16]) = ctx->gmult;
# if defined(GHASH) && !defined(OPENSSL_SMALL_FOOTPRINT)
    void (*gcm_ghash_p) (u64 Xi[2], const u128 Htable[16],
                         const u8 *inp, size_t len) = ctx->ghash;
# endif
#endif

    mlen += len;
    if (mlen > ((U64(1) << 36) - 32) || (sizeof(len) == 8 && mlen < len))
        return -1;
    ctx->len.u[1] = mlen;

    mres = ctx->mres;

    if (ctx->ares) {
        /* First call to encrypt finalizes GHASH(AAD) */
#if defined(GHASH) && !defined(OPENSSL_SMALL_FOOTPRINT)
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
#ifdef BSWAP4
        ctr = BSWAP4(ctx->Yi.d[3]);
#else
        ctr = GETU32(ctx->Yi.c + 12);
#endif
    else
        ctr = ctx->Yi.d[3];

    n = mres % 16;
#if !defined(OPENSSL_SMALL_FOOTPRINT)
    if (16 % sizeof(size_t) == 0) { /* always true actually */
        do {
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
# if defined(STRICT_ALIGNMENT)
            if (((size_t)in | (size_t)out) % sizeof(size_t) != 0)
                break;
# endif
# if defined(GHASH)
            if (len >= 16 && mres) {
                GHASH(ctx, ctx->Xn, mres);
                mres = 0;
            }
#  if defined(GHASH_CHUNK)
            while (len >= GHASH_CHUNK) {
                size_t j = GHASH_CHUNK;

                while (j) {
                    size_t *out_t = (size_t *)out;
                    const size_t *in_t = (const size_t *)in;

                    (*block) (ctx->Yi.c, ctx->EKi.c, key);
                    ++ctr;
                    if (is_endian.little)
#   ifdef BSWAP4
                        ctx->Yi.d[3] = BSWAP4(ctr);
#   else
                        PUTU32(ctx->Yi.c + 12, ctr);
#   endif
                    else
                        ctx->Yi.d[3] = ctr;
                    for (i = 0; i < 16 / sizeof(size_t); ++i)
                        out_t[i] = in_t[i] ^ ctx->EKi.t[i];
                    out += 16;
                    in += 16;
                    j -= 16;
                }
                GHASH(ctx, out - GHASH_CHUNK, GHASH_CHUNK);
                len -= GHASH_CHUNK;
            }
#  endif
            if ((i = (len & (size_t)-16))) {
                size_t j = i;

                while (len >= 16) {
                    size_t *out_t = (size_t *)out;
                    const size_t *in_t = (const size_t *)in;

                    (*block) (ctx->Yi.c, ctx->EKi.c, key);
                    ++ctr;
                    if (is_endian.little)
#  ifdef BSWAP4
                        ctx->Yi.d[3] = BSWAP4(ctr);
#  else
                        PUTU32(ctx->Yi.c + 12, ctr);
#  endif
                    else
                        ctx->Yi.d[3] = ctr;
                    for (i = 0; i < 16 / sizeof(size_t); ++i)
                        out_t[i] = in_t[i] ^ ctx->EKi.t[i];
                    out += 16;
                    in += 16;
                    len -= 16;
                }
                GHASH(ctx, out - j, j);
            }
# else
            while (len >= 16) {
                size_t *out_t = (size_t *)out;
                const size_t *in_t = (const size_t *)in;

                (*block) (ctx->Yi.c, ctx->EKi.c, key);
                ++ctr;
                if (is_endian.little)
#  ifdef BSWAP4
                    ctx->Yi.d[3] = BSWAP4(ctr);
#  else
                    PUTU32(ctx->Yi.c + 12, ctr);
#  endif
                else
                    ctx->Yi.d[3] = ctr;
                for (i = 0; i < 16 / sizeof(size_t); ++i)
                    ctx->Xi.t[i] ^= out_t[i] = in_t[i] ^ ctx->EKi.t[i];
                GCM_MUL(ctx);
                out += 16;
                in += 16;
                len -= 16;
            }
# endif
            if (len) {
                (*block) (ctx->Yi.c, ctx->EKi.c, key);
                ++ctr;
                if (is_endian.little)
# ifdef BSWAP4
                    ctx->Yi.d[3] = BSWAP4(ctr);
# else
                    PUTU32(ctx->Yi.c + 12, ctr);
# endif
                else
                    ctx->Yi.d[3] = ctr;
# if defined(GHASH)
                while (len--) {
                    ctx->Xn[mres++] = out[n] = in[n] ^ ctx->EKi.c[n];
                    ++n;
                }
# else
                while (len--) {
                    ctx->Xi.c[n] ^= out[n] = in[n] ^ ctx->EKi.c[n];
                    ++n;
                }
                mres = n;
# endif
            }

            ctx->mres = mres;
            return 0;
        } while (0);
    }
#endif
    for (i = 0; i < len; ++i) {
        if (n == 0) {
            (*block) (ctx->Yi.c, ctx->EKi.c, key);
            ++ctr;
            if (is_endian.little)
#ifdef BSWAP4
                ctx->Yi.d[3] = BSWAP4(ctr);
#else
                PUTU32(ctx->Yi.c + 12, ctr);
#endif
            else
                ctx->Yi.d[3] = ctr;
        }
#if defined(GHASH) && !defined(OPENSSL_SMALL_FOOTPRINT)
        ctx->Xn[mres++] = out[i] = in[i] ^ ctx->EKi.c[n];
        n = (n + 1) % 16;
        if (mres == sizeof(ctx->Xn)) {
            GHASH(ctx,ctx->Xn,sizeof(ctx->Xn));
            mres = 0;
        }
#else
        ctx->Xi.c[n] ^= out[i] = in[i] ^ ctx->EKi.c[n];
        mres = n = (n + 1) % 16;
        if (n == 0)
            GCM_MUL(ctx);
#endif
    }

    ctx->mres = mres;
    return 0;
}