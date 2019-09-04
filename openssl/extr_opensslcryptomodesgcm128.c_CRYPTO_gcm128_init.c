#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  (* block128_f ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;
struct TYPE_5__ {int* u; int /*<<< orphan*/ * c; } ;
struct TYPE_6__ {TYPE_1__ H; void* key; int /*<<< orphan*/  (* block ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;} ;
typedef  TYPE_2__ GCM128_CONTEXT ;

/* Variables and functions */
 int GETU32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

void CRYPTO_gcm128_init(GCM128_CONTEXT *ctx, void *key, block128_f block)
{
    const union {
        long one;
        char little;
    } is_endian = { 1 };

    memset(ctx, 0, sizeof(*ctx));
    ctx->block = block;
    ctx->key = key;

    (*block) (ctx->H.c, ctx->H.c, key);

    if (is_endian.little) {
        /* H is stored in host byte order */
#ifdef BSWAP8
        ctx->H.u[0] = BSWAP8(ctx->H.u[0]);
        ctx->H.u[1] = BSWAP8(ctx->H.u[1]);
#else
        u8 *p = ctx->H.c;
        u64 hi, lo;
        hi = (u64)GETU32(p) << 32 | GETU32(p + 4);
        lo = (u64)GETU32(p + 8) << 32 | GETU32(p + 12);
        ctx->H.u[0] = hi;
        ctx->H.u[1] = lo;
#endif
    }
#if     TABLE_BITS==8
    gcm_init_8bit(ctx->Htable, ctx->H.u);
#elif   TABLE_BITS==4
# if    defined(GHASH)
#  define CTX__GHASH(f) (ctx->ghash = (f))
# else
#  define CTX__GHASH(f) (ctx->ghash = NULL)
# endif
# if    defined(GHASH_ASM_X86_OR_64)
#  if   !defined(GHASH_ASM_X86) || defined(OPENSSL_IA32_SSE2)
    if (OPENSSL_ia32cap_P[1] & (1 << 1)) { /* check PCLMULQDQ bit */
        if (((OPENSSL_ia32cap_P[1] >> 22) & 0x41) == 0x41) { /* AVX+MOVBE */
            gcm_init_avx(ctx->Htable, ctx->H.u);
            ctx->gmult = gcm_gmult_avx;
            CTX__GHASH(gcm_ghash_avx);
        } else {
            gcm_init_clmul(ctx->Htable, ctx->H.u);
            ctx->gmult = gcm_gmult_clmul;
            CTX__GHASH(gcm_ghash_clmul);
        }
        return;
    }
#  endif
    gcm_init_4bit(ctx->Htable, ctx->H.u);
#  if   defined(GHASH_ASM_X86)  /* x86 only */
#   if  defined(OPENSSL_IA32_SSE2)
    if (OPENSSL_ia32cap_P[0] & (1 << 25)) { /* check SSE bit */
#   else
    if (OPENSSL_ia32cap_P[0] & (1 << 23)) { /* check MMX bit */
#   endif
        ctx->gmult = gcm_gmult_4bit_mmx;
        CTX__GHASH(gcm_ghash_4bit_mmx);
    } else {
        ctx->gmult = gcm_gmult_4bit_x86;
        CTX__GHASH(gcm_ghash_4bit_x86);
    }
#  else
    ctx->gmult = gcm_gmult_4bit;
    CTX__GHASH(gcm_ghash_4bit);
#  endif
# elif  defined(GHASH_ASM_ARM)
#  ifdef PMULL_CAPABLE
    if (PMULL_CAPABLE) {
        gcm_init_v8(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_v8;
        CTX__GHASH(gcm_ghash_v8);
    } else
#  endif
#  ifdef NEON_CAPABLE
    if (NEON_CAPABLE) {
        gcm_init_neon(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_neon;
        CTX__GHASH(gcm_ghash_neon);
    } else
#  endif
    {
        gcm_init_4bit(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_4bit;
        CTX__GHASH(gcm_ghash_4bit);
    }
# elif  defined(GHASH_ASM_SPARC)
    if (OPENSSL_sparcv9cap_P[0] & SPARCV9_VIS3) {
        gcm_init_vis3(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_vis3;
        CTX__GHASH(gcm_ghash_vis3);
    } else {
        gcm_init_4bit(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_4bit;
        CTX__GHASH(gcm_ghash_4bit);
    }
# elif  defined(GHASH_ASM_PPC)
    if (OPENSSL_ppccap_P & PPC_CRYPTO207) {
        gcm_init_p8(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_p8;
        CTX__GHASH(gcm_ghash_p8);
    } else {
        gcm_init_4bit(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_4bit;
        CTX__GHASH(gcm_ghash_4bit);
    }
# else
    gcm_init_4bit(ctx->Htable, ctx->H.u);
# endif
# undef CTX__GHASH
#endif
}