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
struct tcp_fastopen_context {int /*<<< orphan*/  rcu; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_fastopen_ctx_lock; int /*<<< orphan*/  tcp_fastopen_ctx; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tcp_fastopen_context* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_fastopen_ctx_free ; 

void tcp_fastopen_ctx_destroy(struct net *net)
{
	struct tcp_fastopen_context *ctxt;

	spin_lock(&net->ipv4.tcp_fastopen_ctx_lock);

	ctxt = rcu_dereference_protected(net->ipv4.tcp_fastopen_ctx,
				lockdep_is_held(&net->ipv4.tcp_fastopen_ctx_lock));
	rcu_assign_pointer(net->ipv4.tcp_fastopen_ctx, NULL);
	spin_unlock(&net->ipv4.tcp_fastopen_ctx_lock);

	if (ctxt)
		call_rcu(&ctxt->rcu, tcp_fastopen_ctx_free);
}