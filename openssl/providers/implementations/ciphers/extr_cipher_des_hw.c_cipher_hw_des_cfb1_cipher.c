#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  enc; scalar_t__ iv; } ;
struct TYPE_5__ {int /*<<< orphan*/  ks; } ;
struct TYPE_6__ {TYPE_1__ dks; } ;
typedef  TYPE_2__ PROV_DES_CTX ;
typedef  TYPE_3__ PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_cfb_encrypt (unsigned char*,unsigned char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAXCHUNK ; 

__attribute__((used)) static int cipher_hw_des_cfb1_cipher(PROV_CIPHER_CTX *ctx, unsigned char *out,
                                     const unsigned char *in, size_t inl)
{
    size_t n, chunk = MAXCHUNK / 8;
    DES_key_schedule *key = &(((PROV_DES_CTX *)ctx)->dks.ks);
    unsigned char c[1], d[1];

    if (inl < chunk)
        chunk = inl;

    while (inl && inl >= chunk) {
        for (n = 0; n < chunk * 8; ++n) {
            c[0] = (in[n / 8] & (1 << (7 - n % 8))) ? 0x80 : 0;
            DES_cfb_encrypt(c, d, 1, 1, key, (DES_cblock *)ctx->iv, ctx->enc);
            out[n / 8] =
                (out[n / 8] & ~(0x80 >> (unsigned int)(n % 8))) |
                ((d[0] & 0x80) >> (unsigned int)(n % 8));
        }
        inl -= chunk;
        in += chunk;
        out += chunk;
        if (inl < chunk)
            chunk = inl;
    }

    return 1;
}