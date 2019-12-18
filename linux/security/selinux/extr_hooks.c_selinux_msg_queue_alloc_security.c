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
typedef  int /*<<< orphan*/  u32 ;
struct kern_ipc_perm {int /*<<< orphan*/  key; } ;
struct ipc_security_struct {int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipc_id; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_AUDIT_DATA_IPC ; 
 int /*<<< orphan*/  MSGQ__CREATE ; 
 int /*<<< orphan*/  SECCLASS_MSGQ ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  ipc_init_security (struct ipc_security_struct*,int /*<<< orphan*/ ) ; 
 struct ipc_security_struct* selinux_ipc (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_msg_queue_alloc_security(struct kern_ipc_perm *msq)
{
	struct ipc_security_struct *isec;
	struct common_audit_data ad;
	u32 sid = current_sid();
	int rc;

	isec = selinux_ipc(msq);
	ipc_init_security(isec, SECCLASS_MSGQ);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;

	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_MSGQ,
			  MSGQ__CREATE, &ad);
	return rc;
}