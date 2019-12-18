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
struct tls_offload_context_tx {int /*<<< orphan*/  aead_send; scalar_t__ open_record; } ;
struct tls_context {scalar_t__ tx_conf; int /*<<< orphan*/  refcount; int /*<<< orphan*/  (* sk_destruct ) (struct sock*) ;} ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ TLS_HW ; 
 int /*<<< orphan*/  clean_acked_data_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_all_records (struct tls_offload_context_tx*) ; 
 int /*<<< orphan*/  destroy_record (scalar_t__) ; 
 int /*<<< orphan*/  inet_csk (struct sock*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tls_device_queue_ctx_destruction (struct tls_context*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_offload_context_tx* tls_offload_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static void tls_device_sk_destruct(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_offload_context_tx *ctx = tls_offload_ctx_tx(tls_ctx);

	tls_ctx->sk_destruct(sk);

	if (tls_ctx->tx_conf == TLS_HW) {
		if (ctx->open_record)
			destroy_record(ctx->open_record);
		delete_all_records(ctx);
		crypto_free_aead(ctx->aead_send);
		clean_acked_data_disable(inet_csk(sk));
	}

	if (refcount_dec_and_test(&tls_ctx->refcount))
		tls_device_queue_ctx_destruction(tls_ctx);
}