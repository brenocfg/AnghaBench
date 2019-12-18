#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  enc; scalar_t__ iv; } ;
struct TYPE_4__ {int /*<<< orphan*/  ks3; int /*<<< orphan*/  ks2; int /*<<< orphan*/  ks1; } ;
typedef  TYPE_1__ PROV_TDES_CTX ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_ede3_cfb_encrypt (unsigned char*,unsigned char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_CIPH_FLAG_LENGTH_BITS ; 

__attribute__((used)) static int cipher_hw_tdes_cfb1(PROV_CIPHER_CTX *ctx, unsigned char *out,
                               const unsigned char *in, size_t inl)
{
    PROV_TDES_CTX *tctx = (PROV_TDES_CTX *)ctx;
    size_t n;
    unsigned char c[1], d[1];

    if ((ctx->flags & EVP_CIPH_FLAG_LENGTH_BITS) == 0)
        inl *= 8;
    for (n = 0; n < inl; ++n) {
        c[0] = (in[n / 8] & (1 << (7 - n % 8))) ? 0x80 : 0;
        DES_ede3_cfb_encrypt(c, d, 1, 1,
                             &tctx->ks1, &tctx->ks2, &tctx->ks3,
                             (DES_cblock *)ctx->iv, ctx->enc);
        out[n / 8] = (out[n / 8] & ~(0x80 >> (unsigned int)(n % 8)))
            | ((d[0] & 0x80) >> (unsigned int)(n % 8));
    }

    return 1;
}