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
struct tls_sw_context_rx {int /*<<< orphan*/  strp; int /*<<< orphan*/ * recv_pkt; } ;
struct tls_context {int dummy; } ;
struct strp_msg {unsigned int full_len; unsigned int offset; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __strp_unpause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static bool tls_sw_advance_skb(struct sock *sk, struct sk_buff *skb,
			       unsigned int len)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	if (skb) {
		struct strp_msg *rxm = strp_msg(skb);

		if (len < rxm->full_len) {
			rxm->offset += len;
			rxm->full_len -= len;
			return false;
		}
		consume_skb(skb);
	}

	/* Finished with message */
	ctx->recv_pkt = NULL;
	__strp_unpause(&ctx->strp);

	return true;
}