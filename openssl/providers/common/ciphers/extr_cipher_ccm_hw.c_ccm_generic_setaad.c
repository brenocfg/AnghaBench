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
struct TYPE_3__ {int /*<<< orphan*/  ccm_ctx; } ;
typedef  TYPE_1__ PROV_CCM_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ccm128_aad (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int ccm_generic_setaad(PROV_CCM_CTX *ctx, const unsigned char *aad, size_t alen)
{
    CRYPTO_ccm128_aad(&ctx->ccm_ctx, aad, alen);
    return 1;
}