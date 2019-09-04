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
struct TYPE_6__ {size_t keylen; TYPE_1__* ciph; } ;
struct TYPE_5__ {int (* init ) (TYPE_2__*,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ PROV_AES_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  PROV_AES_KEY_generic_init (TYPE_2__*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_F_AES_DINIT ; 
 int /*<<< orphan*/  PROV_R_INVALID_KEYLEN ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,unsigned char const*,size_t) ; 

__attribute__((used)) static int aes_dinit(void *vctx, const unsigned char *key, size_t keylen,
                     const unsigned char *iv, size_t ivlen)
{
    PROV_AES_KEY *ctx = (PROV_AES_KEY *)vctx;

    if (!PROV_AES_KEY_generic_init(ctx, iv, ivlen, 0)) {
        /* PROVerr already called */
        return 0;
    }
    if (key != NULL) {
        if (keylen != ctx->keylen) {
            PROVerr(PROV_F_AES_DINIT, PROV_R_INVALID_KEYLEN);
            return 0;
        }
        return ctx->ciph->init(ctx, key, ctx->keylen);
    }

    return 1;
}