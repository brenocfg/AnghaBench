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
#define  IPC_INFO 136 
#define  IPC_RMID 135 
#define  IPC_SET 134 
#define  IPC_STAT 133 
 int MAY_READ ; 
 int MAY_READWRITE ; 
#define  SHM_INFO 132 
#define  SHM_LOCK 131 
#define  SHM_STAT 130 
#define  SHM_STAT_ANY 129 
#define  SHM_UNLOCK 128 
 int smk_curacc_shm (struct kern_ipc_perm*,int) ; 

__attribute__((used)) static int smack_shm_shmctl(struct kern_ipc_perm *isp, int cmd)
{
	int may;

	switch (cmd) {
	case IPC_STAT:
	case SHM_STAT:
	case SHM_STAT_ANY:
		may = MAY_READ;
		break;
	case IPC_SET:
	case SHM_LOCK:
	case SHM_UNLOCK:
	case IPC_RMID:
		may = MAY_READWRITE;
		break;
	case IPC_INFO:
	case SHM_INFO:
		/*
		 * System level information.
		 */
		return 0;
	default:
		return -EINVAL;
	}
	return smk_curacc_shm(isp, may);
}