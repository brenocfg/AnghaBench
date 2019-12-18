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
struct rpc_task {int dummy; } ;
struct nfs_client {struct nfs4_slot_table* cl_slot_tbl; } ;
struct nfs4_slot_table {int /*<<< orphan*/  slot_tbl_lock; int /*<<< orphan*/  slot_tbl_waitq; } ;
struct nfs4_slot {int dummy; } ;
struct nfs4_session {struct nfs4_slot_table fc_slot_table; } ;
struct nfs4_sequence_res {int /*<<< orphan*/ * sr_slot; } ;
struct nfs4_sequence_args {scalar_t__ sa_privileged; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs4_slot* ERR_PTR (int /*<<< orphan*/ ) ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct nfs4_slot*) ; 
 int /*<<< orphan*/  RPC_PRIORITY_PRIVILEGED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  nfs41_sequence_res_init (struct nfs4_sequence_res*) ; 
 struct nfs4_slot* nfs4_alloc_slot (struct nfs4_slot_table*) ; 
 struct nfs4_session* nfs4_get_session (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_sequence_attach_slot (struct nfs4_sequence_args*,struct nfs4_sequence_res*,struct nfs4_slot*) ; 
 scalar_t__ nfs4_slot_tbl_draining (struct nfs4_slot_table*) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_sleep_on_priority (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_on_priority_timeout (int /*<<< orphan*/ *,struct rpc_task*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_on_timeout (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs4_setup_sequence (struct nfs4_session*,struct nfs4_sequence_args*) ; 

int nfs4_setup_sequence(struct nfs_client *client,
			struct nfs4_sequence_args *args,
			struct nfs4_sequence_res *res,
			struct rpc_task *task)
{
	struct nfs4_session *session = nfs4_get_session(client);
	struct nfs4_slot_table *tbl  = client->cl_slot_tbl;
	struct nfs4_slot *slot;

	/* slot already allocated? */
	if (res->sr_slot != NULL)
		goto out_start;

	if (session)
		tbl = &session->fc_slot_table;

	spin_lock(&tbl->slot_tbl_lock);
	/* The state manager will wait until the slot table is empty */
	if (nfs4_slot_tbl_draining(tbl) && !args->sa_privileged)
		goto out_sleep;

	slot = nfs4_alloc_slot(tbl);
	if (IS_ERR(slot)) {
		if (slot == ERR_PTR(-ENOMEM))
			goto out_sleep_timeout;
		goto out_sleep;
	}
	spin_unlock(&tbl->slot_tbl_lock);

	nfs4_sequence_attach_slot(args, res, slot);

	trace_nfs4_setup_sequence(session, args);
out_start:
	nfs41_sequence_res_init(res);
	rpc_call_start(task);
	return 0;
out_sleep_timeout:
	/* Try again in 1/4 second */
	if (args->sa_privileged)
		rpc_sleep_on_priority_timeout(&tbl->slot_tbl_waitq, task,
				jiffies + (HZ >> 2), RPC_PRIORITY_PRIVILEGED);
	else
		rpc_sleep_on_timeout(&tbl->slot_tbl_waitq, task,
				NULL, jiffies + (HZ >> 2));
	spin_unlock(&tbl->slot_tbl_lock);
	return -EAGAIN;
out_sleep:
	if (args->sa_privileged)
		rpc_sleep_on_priority(&tbl->slot_tbl_waitq, task,
				RPC_PRIORITY_PRIVILEGED);
	else
		rpc_sleep_on(&tbl->slot_tbl_waitq, task, NULL);
	spin_unlock(&tbl->slot_tbl_lock);
	return -EAGAIN;
}