#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct msqid64_ds {int msg_stime; int msg_rtime; int msg_ctime; int msg_stime_high; int msg_rtime_high; int msg_ctime_high; void* msg_lrpid; void* msg_lspid; int /*<<< orphan*/  msg_qbytes; int /*<<< orphan*/  msg_qnum; int /*<<< orphan*/  msg_cbytes; int /*<<< orphan*/  msg_perm; } ;
struct TYPE_8__ {int id; } ;
struct msg_queue {int q_stime; int q_rtime; int q_ctime; TYPE_1__ q_perm; int /*<<< orphan*/  q_lrpid; int /*<<< orphan*/  q_lspid; int /*<<< orphan*/  q_qbytes; int /*<<< orphan*/  q_qnum; int /*<<< orphan*/  q_cbytes; } ;
struct ipc_namespace {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EIDRM ; 
 int IPC_STAT ; 
 scalar_t__ IS_ERR (struct msg_queue*) ; 
 int MSG_STAT ; 
 int MSG_STAT_ANY ; 
 int PTR_ERR (struct msg_queue*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  audit_ipc_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_lock_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_unlock_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_valid_object (TYPE_1__*) ; 
 scalar_t__ ipcperms (struct ipc_namespace*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_to_ipc64_perm (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct msqid64_ds*,int /*<<< orphan*/ ,int) ; 
 struct msg_queue* msq_obtain_object (struct ipc_namespace*,int) ; 
 struct msg_queue* msq_obtain_object_check (struct ipc_namespace*,int) ; 
 void* pid_vnr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_msg_queue_msgctl (TYPE_1__*,int) ; 

__attribute__((used)) static int msgctl_stat(struct ipc_namespace *ns, int msqid,
			 int cmd, struct msqid64_ds *p)
{
	struct msg_queue *msq;
	int err;

	memset(p, 0, sizeof(*p));

	rcu_read_lock();
	if (cmd == MSG_STAT || cmd == MSG_STAT_ANY) {
		msq = msq_obtain_object(ns, msqid);
		if (IS_ERR(msq)) {
			err = PTR_ERR(msq);
			goto out_unlock;
		}
	} else { /* IPC_STAT */
		msq = msq_obtain_object_check(ns, msqid);
		if (IS_ERR(msq)) {
			err = PTR_ERR(msq);
			goto out_unlock;
		}
	}

	/* see comment for SHM_STAT_ANY */
	if (cmd == MSG_STAT_ANY)
		audit_ipc_obj(&msq->q_perm);
	else {
		err = -EACCES;
		if (ipcperms(ns, &msq->q_perm, S_IRUGO))
			goto out_unlock;
	}

	err = security_msg_queue_msgctl(&msq->q_perm, cmd);
	if (err)
		goto out_unlock;

	ipc_lock_object(&msq->q_perm);

	if (!ipc_valid_object(&msq->q_perm)) {
		ipc_unlock_object(&msq->q_perm);
		err = -EIDRM;
		goto out_unlock;
	}

	kernel_to_ipc64_perm(&msq->q_perm, &p->msg_perm);
	p->msg_stime  = msq->q_stime;
	p->msg_rtime  = msq->q_rtime;
	p->msg_ctime  = msq->q_ctime;
#ifndef CONFIG_64BIT
	p->msg_stime_high = msq->q_stime >> 32;
	p->msg_rtime_high = msq->q_rtime >> 32;
	p->msg_ctime_high = msq->q_ctime >> 32;
#endif
	p->msg_cbytes = msq->q_cbytes;
	p->msg_qnum   = msq->q_qnum;
	p->msg_qbytes = msq->q_qbytes;
	p->msg_lspid  = pid_vnr(msq->q_lspid);
	p->msg_lrpid  = pid_vnr(msq->q_lrpid);

	if (cmd == IPC_STAT) {
		/*
		 * As defined in SUS:
		 * Return 0 on success
		 */
		err = 0;
	} else {
		/*
		 * MSG_STAT and MSG_STAT_ANY (both Linux specific)
		 * Return the full id, including the sequence number
		 */
		err = msq->q_perm.id;
	}

	ipc_unlock_object(&msq->q_perm);
out_unlock:
	rcu_read_unlock();
	return err;
}