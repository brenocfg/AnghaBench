#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mdc_ctx; scalar_t__ use_mdcbuf_filter; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int /*<<< orphan*/  px_md_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mdc_free(void *priv)
{
	PGP_Context *ctx = priv;

	if (ctx->use_mdcbuf_filter)
		return;
	px_md_free(ctx->mdc_ctx);
	ctx->mdc_ctx = NULL;
}