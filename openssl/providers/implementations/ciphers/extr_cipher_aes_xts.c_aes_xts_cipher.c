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
struct TYPE_6__ {int /*<<< orphan*/ * key2; int /*<<< orphan*/ * key1; } ;
struct TYPE_4__ {int /*<<< orphan*/  enc; int /*<<< orphan*/  iv; int /*<<< orphan*/  iv_set; } ;
struct TYPE_5__ {TYPE_1__ base; TYPE_3__ xts; int /*<<< orphan*/  (* stream ) (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ PROV_AES_XTS_CTX ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 scalar_t__ CRYPTO_xts128_encrypt (TYPE_3__*,int /*<<< orphan*/ ,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_XTS_DATA_UNIT_IS_TOO_LARGE ; 
 size_t XTS_MAX_BLOCKS_PER_DATA_UNIT ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aes_xts_cipher(void *vctx, unsigned char *out, size_t *outl,
                          size_t outsize, const unsigned char *in, size_t inl)
{
    PROV_AES_XTS_CTX *ctx = (PROV_AES_XTS_CTX *)vctx;

    if (ctx->xts.key1 == NULL
            || ctx->xts.key2 == NULL
            || !ctx->base.iv_set
            || out == NULL
            || in == NULL
            || inl < AES_BLOCK_SIZE)
        return 0;

    /*
     * Impose a limit of 2^20 blocks per data unit as specifed by
     * IEEE Std 1619-2018.  The earlier and obsolete IEEE Std 1619-2007
     * indicated that this was a SHOULD NOT rather than a MUST NOT.
     * NIST SP 800-38E mandates the same limit.
     */
    if (inl > XTS_MAX_BLOCKS_PER_DATA_UNIT * AES_BLOCK_SIZE) {
        ERR_raise(ERR_LIB_PROV, PROV_R_XTS_DATA_UNIT_IS_TOO_LARGE);
        return 0;
    }

    if (ctx->stream != NULL)
        (*ctx->stream)(in, out, inl, ctx->xts.key1, ctx->xts.key2, ctx->base.iv);
    else if (CRYPTO_xts128_encrypt(&ctx->xts, ctx->base.iv, in, out, inl,
                                   ctx->base.enc))
        return 0;

    *outl = inl;
    return 1;
}