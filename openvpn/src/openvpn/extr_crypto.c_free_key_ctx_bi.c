#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct key_ctx_bi {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 

void
free_key_ctx_bi(struct key_ctx_bi *ctx)
{
    free_key_ctx(&ctx->encrypt);
    free_key_ctx(&ctx->decrypt);
}