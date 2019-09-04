#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iv; int /*<<< orphan*/  rec_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  iv; int /*<<< orphan*/  rec_seq; } ;
struct tls_context {void (* sk_proto_close ) (struct sock*,long) ;scalar_t__ tx_conf; scalar_t__ rx_conf; TYPE_2__ rx; TYPE_1__ tx; struct scatterlist* partially_sent_record; } ;
struct sock {int dummy; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ TLS_BASE ; 
 scalar_t__ TLS_HW_RECORD ; 
 scalar_t__ TLS_SW ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int /*<<< orphan*/ ) ; 
 long sock_sndtimeo (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_complete_pending_work (struct sock*,struct tls_context*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  tls_ctx_free (struct tls_context*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int /*<<< orphan*/  tls_handle_open_record (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_sw_free_resources_rx (struct sock*) ; 
 int /*<<< orphan*/  tls_sw_free_resources_tx (struct sock*) ; 

__attribute__((used)) static void tls_sk_proto_close(struct sock *sk, long timeout)
{
	struct tls_context *ctx = tls_get_ctx(sk);
	long timeo = sock_sndtimeo(sk, 0);
	void (*sk_proto_close)(struct sock *sk, long timeout);
	bool free_ctx = false;

	lock_sock(sk);
	sk_proto_close = ctx->sk_proto_close;

	if ((ctx->tx_conf == TLS_HW_RECORD && ctx->rx_conf == TLS_HW_RECORD) ||
	    (ctx->tx_conf == TLS_BASE && ctx->rx_conf == TLS_BASE)) {
		free_ctx = true;
		goto skip_tx_cleanup;
	}

	if (!tls_complete_pending_work(sk, ctx, 0, &timeo))
		tls_handle_open_record(sk, 0);

	if (ctx->partially_sent_record) {
		struct scatterlist *sg = ctx->partially_sent_record;

		while (1) {
			put_page(sg_page(sg));
			sk_mem_uncharge(sk, sg->length);

			if (sg_is_last(sg))
				break;
			sg++;
		}
	}

	/* We need these for tls_sw_fallback handling of other packets */
	if (ctx->tx_conf == TLS_SW) {
		kfree(ctx->tx.rec_seq);
		kfree(ctx->tx.iv);
		tls_sw_free_resources_tx(sk);
	}

	if (ctx->rx_conf == TLS_SW) {
		kfree(ctx->rx.rec_seq);
		kfree(ctx->rx.iv);
		tls_sw_free_resources_rx(sk);
	}

#ifdef CONFIG_TLS_DEVICE
	if (ctx->rx_conf == TLS_HW)
		tls_device_offload_cleanup_rx(sk);

	if (ctx->tx_conf != TLS_HW && ctx->rx_conf != TLS_HW) {
#else
	{
#endif
		tls_ctx_free(ctx);
		ctx = NULL;
	}

skip_tx_cleanup:
	release_sock(sk);
	sk_proto_close(sk, timeout);
	/* free ctx for TLS_HW_RECORD, used by tcp_set_state
	 * for sk->sk_prot->unhash [tls_hw_unhash]
	 */
	if (free_ctx)
		tls_ctx_free(ctx);
}