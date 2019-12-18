#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sunrpc_net {scalar_t__ pipe_version; } ;
struct rpc_pipe {int /*<<< orphan*/  lock; } ;
struct rpc_cred {TYPE_2__* cr_cred; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int errno; } ;
struct gss_upcall_msg {int /*<<< orphan*/  waitqueue; TYPE_1__ msg; int /*<<< orphan*/ * ctx; struct rpc_pipe* pipe; } ;
struct gss_cred {struct rpc_cred gc_base; } ;
struct gss_auth {struct net* net; } ;
struct TYPE_4__ {int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct gss_upcall_msg*) ; 
 int PTR_ERR (struct gss_upcall_msg*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_cred_set_ctx (struct rpc_cred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_msg (struct gss_upcall_msg*) ; 
 struct gss_upcall_msg* gss_setup_upcall (struct gss_auth*,struct rpc_cred*) ; 
 int /*<<< orphan*/  gssd_running (struct net*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_version_waitqueue ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 
 int /*<<< orphan*/  trace_rpcgss_upcall_result (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  warn_gssd () ; 

__attribute__((used)) static inline int
gss_create_upcall(struct gss_auth *gss_auth, struct gss_cred *gss_cred)
{
	struct net *net = gss_auth->net;
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	struct rpc_pipe *pipe;
	struct rpc_cred *cred = &gss_cred->gc_base;
	struct gss_upcall_msg *gss_msg;
	DEFINE_WAIT(wait);
	int err;

retry:
	err = 0;
	/* if gssd is down, just skip upcalling altogether */
	if (!gssd_running(net)) {
		warn_gssd();
		err = -EACCES;
		goto out;
	}
	gss_msg = gss_setup_upcall(gss_auth, cred);
	if (PTR_ERR(gss_msg) == -EAGAIN) {
		err = wait_event_interruptible_timeout(pipe_version_waitqueue,
				sn->pipe_version >= 0, 15 * HZ);
		if (sn->pipe_version < 0) {
			warn_gssd();
			err = -EACCES;
		}
		if (err < 0)
			goto out;
		goto retry;
	}
	if (IS_ERR(gss_msg)) {
		err = PTR_ERR(gss_msg);
		goto out;
	}
	pipe = gss_msg->pipe;
	for (;;) {
		prepare_to_wait(&gss_msg->waitqueue, &wait, TASK_KILLABLE);
		spin_lock(&pipe->lock);
		if (gss_msg->ctx != NULL || gss_msg->msg.errno < 0) {
			break;
		}
		spin_unlock(&pipe->lock);
		if (fatal_signal_pending(current)) {
			err = -ERESTARTSYS;
			goto out_intr;
		}
		schedule();
	}
	if (gss_msg->ctx)
		gss_cred_set_ctx(cred, gss_msg->ctx);
	else
		err = gss_msg->msg.errno;
	spin_unlock(&pipe->lock);
out_intr:
	finish_wait(&gss_msg->waitqueue, &wait);
	gss_release_msg(gss_msg);
out:
	trace_rpcgss_upcall_result(from_kuid(&init_user_ns,
					     cred->cr_cred->fsuid), err);
	return err;
}