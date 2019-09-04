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
 int EINVAL ; 
#define  GETALL 141 
#define  GETNCNT 140 
#define  GETPID 139 
#define  GETVAL 138 
#define  GETZCNT 137 
#define  IPC_INFO 136 
#define  IPC_RMID 135 
#define  IPC_SET 134 
#define  IPC_STAT 133 
 int MAY_READ ; 
 int MAY_READWRITE ; 
#define  SEM_INFO 132 
#define  SEM_STAT 131 
#define  SEM_STAT_ANY 130 
#define  SETALL 129 
#define  SETVAL 128 
 int smk_curacc_sem (struct kern_ipc_perm*,int) ; 

__attribute__((used)) static int smack_sem_semctl(struct kern_ipc_perm *isp, int cmd)
{
	int may;

	switch (cmd) {
	case GETPID:
	case GETNCNT:
	case GETZCNT:
	case GETVAL:
	case GETALL:
	case IPC_STAT:
	case SEM_STAT:
	case SEM_STAT_ANY:
		may = MAY_READ;
		break;
	case SETVAL:
	case SETALL:
	case IPC_RMID:
	case IPC_SET:
		may = MAY_READWRITE;
		break;
	case IPC_INFO:
	case SEM_INFO:
		/*
		 * System level information
		 */
		return 0;
	default:
		return -EINVAL;
	}

	return smk_curacc_sem(isp, may);
}