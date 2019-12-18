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
 scalar_t__ CRYPTO_ccm128_tag (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int ccm_generic_gettag(PROV_CCM_CTX *ctx, unsigned char *tag, size_t tlen)
{
    return CRYPTO_ccm128_tag(&ctx->ccm_ctx, tag, tlen) > 0;
}