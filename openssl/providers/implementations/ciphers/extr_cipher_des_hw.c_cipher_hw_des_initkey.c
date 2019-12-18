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
struct TYPE_9__ {scalar_t__ mode; scalar_t__ enc; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cbc; } ;
struct TYPE_6__ {int /*<<< orphan*/  ks; } ;
struct TYPE_8__ {TYPE_2__ dstream; TYPE_1__ dks; } ;
typedef  TYPE_3__ PROV_DES_CTX ;
typedef  TYPE_4__ PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPH_CBC_MODE ; 
 scalar_t__ SPARC_DES_CAPABLE ; 
 int /*<<< orphan*/ * des_t4_cbc_decrypt ; 
 int /*<<< orphan*/ * des_t4_cbc_encrypt ; 
 int /*<<< orphan*/  des_t4_key_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipher_hw_des_initkey(PROV_CIPHER_CTX *ctx,
                                 const unsigned char *key, size_t keylen)
{
    PROV_DES_CTX *dctx = (PROV_DES_CTX *)ctx;
    DES_cblock *deskey = (DES_cblock *)key;
    DES_key_schedule *ks = &dctx->dks.ks;

    dctx->dstream.cbc = NULL;
#if defined(SPARC_DES_CAPABLE)
    if (SPARC_DES_CAPABLE) {
        if (ctx->mode == EVP_CIPH_CBC_MODE) {
            des_t4_key_expand(&deskey[0], ks);
            dctx->dstream.cbc = ctx->enc ? des_t4_cbc_encrypt :
                                           des_t4_cbc_decrypt;
            return 1;
        }
    }
#endif
    DES_set_key_unchecked(deskey, ks);
    return 1;
}