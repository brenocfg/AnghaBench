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
struct TYPE_8__ {int id; } ;
struct shmid_kernel {int shm_atim; int shm_dtim; int shm_ctim; TYPE_1__ shm_perm; int /*<<< orphan*/  shm_nattch; int /*<<< orphan*/  shm_lprid; int /*<<< orphan*/  shm_cprid; int /*<<< orphan*/  shm_segsz; } ;
struct shmid64_ds {int shm_atime; int shm_dtime; int shm_ctime; int shm_atime_high; int shm_dtime_high; int shm_ctime_high; int /*<<< orphan*/  shm_nattch; void* shm_lpid; void* shm_cpid; int /*<<< orphan*/  shm_segsz; int /*<<< orphan*/  shm_perm; } ;
struct ipc_namespace {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EIDRM ; 
 int IPC_STAT ; 
 scalar_t__ IS_ERR (struct shmid_kernel*) ; 
 int PTR_ERR (struct shmid_kernel*) ; 
 int SHM_STAT ; 
 int SHM_STAT_ANY ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  audit_ipc_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_lock_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_unlock_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_valid_object (TYPE_1__*) ; 
 scalar_t__ ipcperms (struct ipc_namespace*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_to_ipc64_perm (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct shmid64_ds*,int /*<<< orphan*/ ,int) ; 
 void* pid_vnr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_shm_shmctl (TYPE_1__*,int) ; 
 struct shmid_kernel* shm_obtain_object (struct ipc_namespace*,int) ; 
 struct shmid_kernel* shm_obtain_object_check (struct ipc_namespace*,int) ; 

__attribute__((used)) static int shmctl_stat(struct ipc_namespace *ns, int shmid,
			int cmd, struct shmid64_ds *tbuf)
{
	struct shmid_kernel *shp;
	int err;

	memset(tbuf, 0, sizeof(*tbuf));

	rcu_read_lock();
	if (cmd == SHM_STAT || cmd == SHM_STAT_ANY) {
		shp = shm_obtain_object(ns, shmid);
		if (IS_ERR(shp)) {
			err = PTR_ERR(shp);
			goto out_unlock;
		}
	} else { /* IPC_STAT */
		shp = shm_obtain_object_check(ns, shmid);
		if (IS_ERR(shp)) {
			err = PTR_ERR(shp);
			goto out_unlock;
		}
	}

	/*
	 * Semantically SHM_STAT_ANY ought to be identical to
	 * that functionality provided by the /proc/sysvipc/
	 * interface. As such, only audit these calls and
	 * do not do traditional S_IRUGO permission checks on
	 * the ipc object.
	 */
	if (cmd == SHM_STAT_ANY)
		audit_ipc_obj(&shp->shm_perm);
	else {
		err = -EACCES;
		if (ipcperms(ns, &shp->shm_perm, S_IRUGO))
			goto out_unlock;
	}

	err = security_shm_shmctl(&shp->shm_perm, cmd);
	if (err)
		goto out_unlock;

	ipc_lock_object(&shp->shm_perm);

	if (!ipc_valid_object(&shp->shm_perm)) {
		ipc_unlock_object(&shp->shm_perm);
		err = -EIDRM;
		goto out_unlock;
	}

	kernel_to_ipc64_perm(&shp->shm_perm, &tbuf->shm_perm);
	tbuf->shm_segsz	= shp->shm_segsz;
	tbuf->shm_atime	= shp->shm_atim;
	tbuf->shm_dtime	= shp->shm_dtim;
	tbuf->shm_ctime	= shp->shm_ctim;
#ifndef CONFIG_64BIT
	tbuf->shm_atime_high = shp->shm_atim >> 32;
	tbuf->shm_dtime_high = shp->shm_dtim >> 32;
	tbuf->shm_ctime_high = shp->shm_ctim >> 32;
#endif
	tbuf->shm_cpid	= pid_vnr(shp->shm_cprid);
	tbuf->shm_lpid	= pid_vnr(shp->shm_lprid);
	tbuf->shm_nattch = shp->shm_nattch;

	if (cmd == IPC_STAT) {
		/*
		 * As defined in SUS:
		 * Return 0 on success
		 */
		err = 0;
	} else {
		/*
		 * SHM_STAT and SHM_STAT_ANY (both Linux specific)
		 * Return the full id, including the sequence number
		 */
		err = shp->shm_perm.id;
	}

	ipc_unlock_object(&shp->shm_perm);
out_unlock:
	rcu_read_unlock();
	return err;
}