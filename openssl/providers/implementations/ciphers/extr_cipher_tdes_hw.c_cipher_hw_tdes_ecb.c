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
typedef  int /*<<< orphan*/  const_DES_cblock ;
struct TYPE_5__ {int /*<<< orphan*/  enc; } ;
struct TYPE_4__ {int /*<<< orphan*/  ks3; int /*<<< orphan*/  ks2; int /*<<< orphan*/  ks1; } ;
typedef  TYPE_1__ PROV_TDES_CTX ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 size_t DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DES_ecb3_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cipher_hw_tdes_ecb(PROV_CIPHER_CTX *ctx, unsigned char *out,
                       const unsigned char *in, size_t len)
{
    size_t i;
    PROV_TDES_CTX *tctx = (PROV_TDES_CTX *)ctx;

    if (len < DES_BLOCK_SIZE)
        return 1;

    for (i = 0, len -= DES_BLOCK_SIZE; i <= len; i += DES_BLOCK_SIZE) {
        DES_ecb3_encrypt((const_DES_cblock *)(in + i), (DES_cblock *)(out + i),
                         &tctx->ks1, &tctx->ks2, &tctx->ks3, ctx->enc);
    }
    return 1;
}