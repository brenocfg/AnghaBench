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
typedef  scalar_t__ u32 ;
struct msg_security_struct {scalar_t__ sid; } ;
struct msg_msg {int dummy; } ;
struct kern_ipc_perm {int /*<<< orphan*/  key; } ;
struct ipc_security_struct {scalar_t__ sid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipc_id; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_AUDIT_DATA_IPC ; 
 int /*<<< orphan*/  MSGQ__ENQUEUE ; 
 int /*<<< orphan*/  MSGQ__WRITE ; 
 int /*<<< orphan*/  MSG__SEND ; 
 int /*<<< orphan*/  SECCLASS_MSG ; 
 int /*<<< orphan*/  SECCLASS_MSGQ ; 
 scalar_t__ SECINITSID_UNLABELED ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 scalar_t__ current_sid () ; 
 int security_transition_sid (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct ipc_security_struct* selinux_ipc (struct kern_ipc_perm*) ; 
 struct msg_security_struct* selinux_msg_msg (struct msg_msg*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_msg_queue_msgsnd(struct kern_ipc_perm *msq, struct msg_msg *msg, int msqflg)
{
	struct ipc_security_struct *isec;
	struct msg_security_struct *msec;
	struct common_audit_data ad;
	u32 sid = current_sid();
	int rc;

	isec = selinux_ipc(msq);
	msec = selinux_msg_msg(msg);

	/*
	 * First time through, need to assign label to the message
	 */
	if (msec->sid == SECINITSID_UNLABELED) {
		/*
		 * Compute new sid based on current process and
		 * message queue this message will be stored in
		 */
		rc = security_transition_sid(&selinux_state, sid, isec->sid,
					     SECCLASS_MSG, NULL, &msec->sid);
		if (rc)
			return rc;
	}

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;

	/* Can this process write to the queue? */
	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_MSGQ,
			  MSGQ__WRITE, &ad);
	if (!rc)
		/* Can this process send the message */
		rc = avc_has_perm(&selinux_state,
				  sid, msec->sid, SECCLASS_MSG,
				  MSG__SEND, &ad);
	if (!rc)
		/* Can the message be put in the queue? */
		rc = avc_has_perm(&selinux_state,
				  msec->sid, isec->sid, SECCLASS_MSGQ,
				  MSGQ__ENQUEUE, &ad);

	return rc;
}