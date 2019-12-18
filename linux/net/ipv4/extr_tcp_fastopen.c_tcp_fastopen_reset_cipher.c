#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcp_fastopen_context {int num; int /*<<< orphan*/  rcu; TYPE_1__* key; } ;
struct sock {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tcp_fastopen_ctx_lock; int /*<<< orphan*/  tcp_fastopen_ctx; } ;
struct net {TYPE_3__ ipv4; } ;
struct fastopen_queue {int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {struct fastopen_queue fastopenq; } ;
struct TYPE_8__ {TYPE_2__ icsk_accept_queue; } ;
struct TYPE_5__ {void** key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_unaligned_le64 (void*) ; 
 TYPE_4__* inet_csk (struct sock*) ; 
 struct tcp_fastopen_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tcp_fastopen_context*) ; 
 struct tcp_fastopen_context* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_fastopen_ctx_free ; 

int tcp_fastopen_reset_cipher(struct net *net, struct sock *sk,
			      void *primary_key, void *backup_key)
{
	struct tcp_fastopen_context *ctx, *octx;
	struct fastopen_queue *q;
	int err = 0;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		err = -ENOMEM;
		goto out;
	}

	ctx->key[0].key[0] = get_unaligned_le64(primary_key);
	ctx->key[0].key[1] = get_unaligned_le64(primary_key + 8);
	if (backup_key) {
		ctx->key[1].key[0] = get_unaligned_le64(backup_key);
		ctx->key[1].key[1] = get_unaligned_le64(backup_key + 8);
		ctx->num = 2;
	} else {
		ctx->num = 1;
	}

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
out:
	return err;
}