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
struct tls_sw_context_tx {struct tls_rec* open_rec; } ;
struct tls_rec {int /*<<< orphan*/  msg_encrypted; int /*<<< orphan*/  msg_plaintext; } ;
struct tls_prot_info {scalar_t__ overhead_size; } ;
struct tls_context {struct tls_prot_info prot_info; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_msg_trim (struct sock*,int /*<<< orphan*/ *,int) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static void tls_trim_both_msgs(struct sock *sk, int target_size)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_prot_info *prot = &tls_ctx->prot_info;
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	struct tls_rec *rec = ctx->open_rec;

	sk_msg_trim(sk, &rec->msg_plaintext, target_size);
	if (target_size > 0)
		target_size += prot->overhead_size;
	sk_msg_trim(sk, &rec->msg_encrypted, target_size);
}