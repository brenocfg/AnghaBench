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
struct pdp_ctx {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  hlist_addr; int /*<<< orphan*/  hlist_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdp_context_free ; 

__attribute__((used)) static void pdp_context_delete(struct pdp_ctx *pctx)
{
	hlist_del_rcu(&pctx->hlist_tid);
	hlist_del_rcu(&pctx->hlist_addr);
	call_rcu(&pctx->rcu_head, pdp_context_free);
}