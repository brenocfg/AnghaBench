#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_fastopen_context {int /*<<< orphan*/  rcu; int /*<<< orphan*/  key; int /*<<< orphan*/  tfm; } ;
struct sock {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tcp_fastopen_ctx_lock; int /*<<< orphan*/  tcp_fastopen_ctx; } ;
struct net {TYPE_2__ ipv4; } ;
struct fastopen_queue {int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {struct fastopen_queue fastopenq; } ;
struct TYPE_6__ {TYPE_1__ icsk_accept_queue; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_cipher_setkey (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  kfree (struct tcp_fastopen_context*) ; 
 struct tcp_fastopen_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tcp_fastopen_context*) ; 
 struct tcp_fastopen_context* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_fastopen_ctx_free ; 

int tcp_fastopen_reset_cipher(struct net *net, struct sock *sk,
			      void *key, unsigned int len)
{
	struct tcp_fastopen_context *ctx, *octx;
	struct fastopen_queue *q;
	int err;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx->tfm = crypto_alloc_cipher("aes", 0, 0);

	if (IS_ERR(ctx->tfm)) {
		err = PTR_ERR(ctx->tfm);
error:		kfree(ctx);
		pr_err("TCP: TFO aes cipher alloc error: %d\n", err);
		return err;
	}
	err = crypto_cipher_setkey(ctx->tfm, key, len);
	if (err) {
		pr_err("TCP: TFO cipher key error: %d\n", err);
		crypto_free_cipher(ctx->tfm);
		goto error;
	}
	memcpy(ctx->key, key, len);


	spin_lock(&net->ipv4.tcp_fastopen_ctx_lock);
	if (sk) {
		q = &inet_csk(sk)->icsk_accept_queue.fastopenq;
		octx = rcu_dereference_protected(q->ctx,
			lockdep_is_held(&net->ipv4.tcp_fastopen_ctx_lock));
		rcu_assign_pointer(q->ctx, ctx);
	} else {
		octx = rcu_dereference_protected(net->ipv4.tcp_fastopen_ctx,
			lockdep_is_held(&net->ipv4.tcp_fastopen_ctx_lock));
		rcu_assign_pointer(net->ipv4.tcp_fastopen_ctx, ctx);
	}
	spin_unlock(&net->ipv4.tcp_fastopen_ctx_lock);

	if (octx)
		call_rcu(&octx->rcu, tcp_fastopen_ctx_free);
	return err;
}