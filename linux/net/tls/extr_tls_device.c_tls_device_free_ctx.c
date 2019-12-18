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
struct TYPE_2__ {int /*<<< orphan*/  iv; int /*<<< orphan*/  rec_seq; } ;
struct tls_context {scalar_t__ tx_conf; scalar_t__ rx_conf; TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ TLS_HW ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_free (int /*<<< orphan*/ *,struct tls_context*) ; 
 int /*<<< orphan*/  tls_offload_ctx_rx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_offload_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static void tls_device_free_ctx(struct tls_context *ctx)
{
	if (ctx->tx_conf == TLS_HW) {
		kfree(tls_offload_ctx_tx(ctx));
		kfree(ctx->tx.rec_seq);
		kfree(ctx->tx.iv);
	}

	if (ctx->rx_conf == TLS_HW)
		kfree(tls_offload_ctx_rx(ctx));

	tls_ctx_free(NULL, ctx);
}