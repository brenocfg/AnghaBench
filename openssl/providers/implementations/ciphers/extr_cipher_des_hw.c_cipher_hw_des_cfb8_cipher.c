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
 int /*<<< orphan*/  DES_cfb_encrypt (unsigned char const*,unsigned char*,int,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t MAXCHUNK ; 

__attribute__((used)) static int cipher_hw_des_cfb8_cipher(PROV_CIPHER_CTX *ctx, unsigned char *out,
                                     const unsigned char *in, size_t inl)
{
    DES_key_schedule *key = &(((PROV_DES_CTX *)ctx)->dks.ks);

    while (inl >= MAXCHUNK) {
        DES_cfb_encrypt(in, out, 8, (long)MAXCHUNK, key,
                        (DES_cblock *)ctx->iv, ctx->enc);
        inl -= MAXCHUNK;
        in += MAXCHUNK;
        out += MAXCHUNK;
    }
    if (inl > 0)
        DES_cfb_encrypt(in, out, 8, (long)inl, key,
                        (DES_cblock *)ctx->iv, ctx->enc);
    return 1;
}