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
struct tls_sw_context_rx {int decrypted; int /*<<< orphan*/  (* saved_data_ready ) (int /*<<< orphan*/ ) ;struct sk_buff* recv_pkt; } ;
struct tls_context {int dummy; } ;
struct strparser {int /*<<< orphan*/  sk; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strp_pause (struct strparser*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct tls_context* tls_get_ctx (int /*<<< orphan*/ ) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static void tls_queue(struct strparser *strp, struct sk_buff *skb)
{
	struct tls_context *tls_ctx = tls_get_ctx(strp->sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	ctx->decrypted = false;

	ctx->recv_pkt = skb;
	strp_pause(strp);

	ctx->saved_data_ready(strp->sk);
}