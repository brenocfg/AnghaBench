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
struct tcp_fastopen_context {int /*<<< orphan*/  rcu; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {TYPE_1__ fastopenq; } ;
struct TYPE_6__ {TYPE_2__ icsk_accept_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 struct tcp_fastopen_context* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_fastopen_ctx_free ; 

void tcp_fastopen_destroy_cipher(struct sock *sk)
{
	struct tcp_fastopen_context *ctx;

	ctx = rcu_dereference_protected(
			inet_csk(sk)->icsk_accept_queue.fastopenq.ctx, 1);
	if (ctx)
		call_rcu(&ctx->rcu, tcp_fastopen_ctx_free);
}