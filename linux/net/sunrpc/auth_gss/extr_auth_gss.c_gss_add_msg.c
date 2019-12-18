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
struct rpc_pipe {int /*<<< orphan*/  lock; int /*<<< orphan*/  in_downcall; } ;
struct gss_upcall_msg {int /*<<< orphan*/  list; int /*<<< orphan*/  count; int /*<<< orphan*/  auth; int /*<<< orphan*/  uid; struct rpc_pipe* pipe; } ;

/* Variables and functions */
 struct gss_upcall_msg* __gss_find_upcall (struct rpc_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct gss_upcall_msg *
gss_add_msg(struct gss_upcall_msg *gss_msg)
{
	struct rpc_pipe *pipe = gss_msg->pipe;
	struct gss_upcall_msg *old;

	spin_lock(&pipe->lock);
	old = __gss_find_upcall(pipe, gss_msg->uid, gss_msg->auth);
	if (old == NULL) {
		refcount_inc(&gss_msg->count);
		list_add(&gss_msg->list, &pipe->in_downcall);
	} else
		gss_msg = old;
	spin_unlock(&pipe->lock);
	return gss_msg;
}