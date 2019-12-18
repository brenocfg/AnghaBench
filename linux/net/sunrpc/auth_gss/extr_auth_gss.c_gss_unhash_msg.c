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
struct rpc_pipe {int /*<<< orphan*/  lock; } ;
struct gss_upcall_msg {int /*<<< orphan*/  list; struct rpc_pipe* pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gss_unhash_msg (struct gss_upcall_msg*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gss_unhash_msg(struct gss_upcall_msg *gss_msg)
{
	struct rpc_pipe *pipe = gss_msg->pipe;

	if (list_empty(&gss_msg->list))
		return;
	spin_lock(&pipe->lock);
	if (!list_empty(&gss_msg->list))
		__gss_unhash_msg(gss_msg);
	spin_unlock(&pipe->lock);
}