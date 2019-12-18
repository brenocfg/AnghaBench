#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_l_index; int /*<<< orphan*/  l; } ;
typedef  TYPE_1__ OCB128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int) ; 

void CRYPTO_ocb128_cleanup(OCB128_CONTEXT *ctx)
{
    if (ctx) {
        OPENSSL_clear_free(ctx->l, ctx->max_l_index * 16);
        OPENSSL_cleanse(ctx, sizeof(*ctx));
    }
}