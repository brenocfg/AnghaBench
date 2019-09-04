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
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
#define  IPC_INFO 134 
#define  IPC_RMID 133 
#define  IPC_SET 132 
#define  IPC_STAT 131 
 int MSGQ__ASSOCIATE ; 
 int MSGQ__DESTROY ; 
 int MSGQ__GETATTR ; 
 int MSGQ__SETATTR ; 
#define  MSG_INFO 130 
#define  MSG_STAT 129 
#define  MSG_STAT_ANY 128 
 int /*<<< orphan*/  SECCLASS_SYSTEM ; 
 int /*<<< orphan*/  SECINITSID_KERNEL ; 
 int /*<<< orphan*/  SYSTEM__IPC_INFO ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int ipc_has_perm (struct kern_ipc_perm*,int) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_msg_queue_msgctl(struct kern_ipc_perm *msq, int cmd)
{
	int err;
	int perms;

	switch (cmd) {
	case IPC_INFO:
	case MSG_INFO:
		/* No specific object, just general system-wide information. */
		return avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__IPC_INFO, NULL);
	case IPC_STAT:
	case MSG_STAT:
	case MSG_STAT_ANY:
		perms = MSGQ__GETATTR | MSGQ__ASSOCIATE;
		break;
	case IPC_SET:
		perms = MSGQ__SETATTR;
		break;
	case IPC_RMID:
		perms = MSGQ__DESTROY;
		break;
	default:
		return 0;
	}

	err = ipc_has_perm(msq, perms);
	return err;
}