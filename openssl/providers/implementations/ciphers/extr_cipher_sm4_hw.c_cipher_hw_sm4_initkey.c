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
typedef  void* block128_f ;
struct TYPE_7__ {scalar_t__ mode; void* block; scalar_t__ enc; int /*<<< orphan*/ * ks; } ;
struct TYPE_5__ {int /*<<< orphan*/  ks; } ;
struct TYPE_6__ {TYPE_1__ ks; } ;
typedef  int /*<<< orphan*/  SM4_KEY ;
typedef  TYPE_2__ PROV_SM4_CTX ;
typedef  TYPE_3__ PROV_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ EVP_CIPH_CBC_MODE ; 
 scalar_t__ EVP_CIPH_ECB_MODE ; 
 scalar_t__ SM4_decrypt ; 
 scalar_t__ SM4_encrypt ; 
 int /*<<< orphan*/  SM4_set_key (unsigned char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipher_hw_sm4_initkey(PROV_CIPHER_CTX *ctx,
                                 const unsigned char *key, size_t keylen)
{
    PROV_SM4_CTX *sctx =  (PROV_SM4_CTX *)ctx;
    SM4_KEY *ks = &sctx->ks.ks;

    SM4_set_key(key, ks);
    ctx->ks = ks;
    if (ctx->enc
            || (ctx->mode != EVP_CIPH_ECB_MODE
                && ctx->mode != EVP_CIPH_CBC_MODE))
        ctx->block = (block128_f)SM4_encrypt;
    else
        ctx->block = (block128_f)SM4_decrypt;
    return 1;
}