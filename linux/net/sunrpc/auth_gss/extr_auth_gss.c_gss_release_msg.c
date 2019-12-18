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
struct net {int dummy; } ;
struct gss_upcall_msg {int /*<<< orphan*/  service_name; TYPE_1__* auth; int /*<<< orphan*/  rpc_waitqueue; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  list; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {struct net* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  gss_put_auth (TYPE_1__*) ; 
 int /*<<< orphan*/  gss_put_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gss_upcall_msg*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pipe_version (struct net*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gss_release_msg(struct gss_upcall_msg *gss_msg)
{
	struct net *net = gss_msg->auth->net;
	if (!refcount_dec_and_test(&gss_msg->count))
		return;
	put_pipe_version(net);
	BUG_ON(!list_empty(&gss_msg->list));
	if (gss_msg->ctx != NULL)
		gss_put_ctx(gss_msg->ctx);
	rpc_destroy_wait_queue(&gss_msg->rpc_waitqueue);
	gss_put_auth(gss_msg->auth);
	kfree_const(gss_msg->service_name);
	kfree(gss_msg);
}