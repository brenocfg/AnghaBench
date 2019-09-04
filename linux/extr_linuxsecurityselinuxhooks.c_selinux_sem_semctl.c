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
typedef  int u32 ;
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
#define  GETALL 141 
#define  GETNCNT 140 
#define  GETPID 139 
#define  GETVAL 138 
#define  GETZCNT 137 
#define  IPC_INFO 136 
#define  IPC_RMID 135 
#define  IPC_SET 134 
#define  IPC_STAT 133 
 int /*<<< orphan*/  SECCLASS_SYSTEM ; 
 int /*<<< orphan*/  SECINITSID_KERNEL ; 
#define  SEM_INFO 132 
#define  SEM_STAT 131 
#define  SEM_STAT_ANY 130 
 int SEM__ASSOCIATE ; 
 int SEM__DESTROY ; 
 int SEM__GETATTR ; 
 int SEM__READ ; 
 int SEM__SETATTR ; 
 int SEM__WRITE ; 
#define  SETALL 129 
#define  SETVAL 128 
 int /*<<< orphan*/  SYSTEM__IPC_INFO ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int ipc_has_perm (struct kern_ipc_perm*,int) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_sem_semctl(struct kern_ipc_perm *sma, int cmd)
{
	int err;
	u32 perms;

	switch (cmd) {
	case IPC_INFO:
	case SEM_INFO:
		/* No specific object, just general system-wide information. */
		return avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__IPC_INFO, NULL);
	case GETPID:
	case GETNCNT:
	case GETZCNT:
		perms = SEM__GETATTR;
		break;
	case GETVAL:
	case GETALL:
		perms = SEM__READ;
		break;
	case SETVAL:
	case SETALL:
		perms = SEM__WRITE;
		break;
	case IPC_RMID:
		perms = SEM__DESTROY;
		break;
	case IPC_SET:
		perms = SEM__SETATTR;
		break;
	case IPC_STAT:
	case SEM_STAT:
	case SEM_STAT_ANY:
		perms = SEM__GETATTR | SEM__ASSOCIATE;
		break;
	default:
		return 0;
	}

	err = ipc_has_perm(sma, perms);
	return err;
}