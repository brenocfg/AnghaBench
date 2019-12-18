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
#define  IPC_INFO 136 
#define  IPC_RMID 135 
#define  IPC_SET 134 
#define  IPC_STAT 133 
 int /*<<< orphan*/  SECCLASS_SYSTEM ; 
 int /*<<< orphan*/  SECINITSID_KERNEL ; 
#define  SHM_INFO 132 
#define  SHM_LOCK 131 
#define  SHM_STAT 130 
#define  SHM_STAT_ANY 129 
#define  SHM_UNLOCK 128 
 int SHM__ASSOCIATE ; 
 int SHM__DESTROY ; 
 int SHM__GETATTR ; 
 int SHM__LOCK ; 
 int SHM__SETATTR ; 
 int /*<<< orphan*/  SYSTEM__IPC_INFO ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int ipc_has_perm (struct kern_ipc_perm*,int) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_shm_shmctl(struct kern_ipc_perm *shp, int cmd)
{
	int perms;
	int err;

	switch (cmd) {
	case IPC_INFO:
	case SHM_INFO:
		/* No specific object, just general system-wide information. */
		return avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__IPC_INFO, NULL);
	case IPC_STAT:
	case SHM_STAT:
	case SHM_STAT_ANY:
		perms = SHM__GETATTR | SHM__ASSOCIATE;
		break;
	case IPC_SET:
		perms = SHM__SETATTR;
		break;
	case SHM_LOCK:
	case SHM_UNLOCK:
		perms = SHM__LOCK;
		break;
	case IPC_RMID:
		perms = SHM__DESTROY;
		break;
	default:
		return 0;
	}

	err = ipc_has_perm(shp, perms);
	return err;
}