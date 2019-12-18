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
struct sock {int /*<<< orphan*/  sk_write_pending; } ;

/* Variables and functions */
 scalar_t__ TLS_HW ; 
 scalar_t__ TLS_SW ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_device_free_resources_tx (struct sock*) ; 
 int /*<<< orphan*/  tls_device_offload_cleanup_rx (struct sock*) ; 
 int /*<<< orphan*/  tls_handle_open_record (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_sw_release_resources_rx (struct sock*) ; 
 int /*<<< orphan*/  tls_sw_release_resources_tx (struct sock*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_pending_writer (struct sock*,long*) ; 

__attribute__((used)) static void tls_sk_proto_cleanup(struct sock *sk,
				 struct tls_context *ctx, long timeo)
{
	if (unlikely(sk->sk_write_pending) &&
	    !wait_on_pending_writer(sk, &timeo))
		tls_handle_open_record(sk, 0);

	/* We need these for tls_sw_fallback handling of other packets */
	if (ctx->tx_conf == TLS_SW) {
		kfree(ctx->tx.rec_seq);
		kfree(ctx->tx.iv);
		tls_sw_release_resources_tx(sk);
	} else if (ctx->tx_conf == TLS_HW) {
		tls_device_free_resources_tx(sk);
	}

	if (ctx->rx_conf == TLS_SW)
		tls_sw_release_resources_rx(sk);
	else if (ctx->rx_conf == TLS_HW)
		tls_device_offload_cleanup_rx(sk);
}