#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  enc; scalar_t__ iv; } ;
struct TYPE_7__ {int /*<<< orphan*/  ks; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cbc ) (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  ks3; int /*<<< orphan*/  ks2; int /*<<< orphan*/  ks1; TYPE_2__ tks; TYPE_1__ tstream; } ;
typedef  TYPE_3__ PROV_TDES_CTX ;
typedef  TYPE_4__ PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_ede3_cbc_encrypt (unsigned char const*,unsigned char*,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t MAXCHUNK ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,scalar_t__) ; 

int cipher_hw_tdes_cbc(PROV_CIPHER_CTX *ctx, unsigned char *out,
                       const unsigned char *in, size_t inl)
{
    PROV_TDES_CTX *tctx = (PROV_TDES_CTX *)ctx;

    if (tctx->tstream.cbc != NULL) {
        (*tctx->tstream.cbc) (in, out, inl, tctx->tks.ks, ctx->iv);
        return 1;
    }

    while (inl >= MAXCHUNK) {
        DES_ede3_cbc_encrypt(in, out, (long)MAXCHUNK, &tctx->ks1, &tctx->ks2,
                             &tctx->ks3, (DES_cblock *)ctx->iv, ctx->enc);
        inl -= MAXCHUNK;
        in += MAXCHUNK;
        out += MAXCHUNK;
    }
    if (inl > 0)
        DES_ede3_cbc_encrypt(in, out, (long)inl, &tctx->ks1, &tctx->ks2,
                             &tctx->ks3, (DES_cblock *)ctx->iv, ctx->enc);
    return 1;
}