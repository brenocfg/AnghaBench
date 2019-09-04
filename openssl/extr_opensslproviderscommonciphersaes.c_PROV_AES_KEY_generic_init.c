#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mode; int enc; int /*<<< orphan*/  iv; } ;
typedef  TYPE_1__ PROV_AES_KEY ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_CIPH_ECB_MODE ; 
 int /*<<< orphan*/  PROV_F_PROV_AES_KEY_GENERIC_INIT ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

__attribute__((used)) static int PROV_AES_KEY_generic_init(PROV_AES_KEY *ctx,
                                      const unsigned char *iv,
                                      size_t ivlen,
                                      int enc)
{
    if (iv != NULL && ctx->mode != EVP_CIPH_ECB_MODE) {
        if (ivlen != AES_BLOCK_SIZE) {
            PROVerr(PROV_F_PROV_AES_KEY_GENERIC_INIT, ERR_R_INTERNAL_ERROR);
            return 0;
        }
        memcpy(ctx->iv, iv, AES_BLOCK_SIZE);
    }
    ctx->enc = enc;

    return 1;
}