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
struct TYPE_3__ {int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  o_ctx; int /*<<< orphan*/  i_ctx; } ;
typedef  TYPE_1__ HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ ,unsigned long) ; 

void HMAC_CTX_set_flags(HMAC_CTX *ctx, unsigned long flags)
{
    EVP_MD_CTX_set_flags(ctx->i_ctx, flags);
    EVP_MD_CTX_set_flags(ctx->o_ctx, flags);
    EVP_MD_CTX_set_flags(ctx->md_ctx, flags);
}