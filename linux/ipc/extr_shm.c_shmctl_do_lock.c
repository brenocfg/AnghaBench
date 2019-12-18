#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct user_struct {int dummy; } ;
struct TYPE_6__ {int mode; int /*<<< orphan*/  cuid; int /*<<< orphan*/  uid; } ;
struct shmid_kernel {TYPE_1__ shm_perm; struct user_struct* mlock_user; struct file* shm_file; } ;
struct ipc_namespace {int /*<<< orphan*/  user_ns; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int EIDRM ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct shmid_kernel*) ; 
 int PTR_ERR (struct shmid_kernel*) ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int SHM_LOCK ; 
 int SHM_LOCKED ; 
 int /*<<< orphan*/  audit_ipc_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  current_euid () ; 
 struct user_struct* current_user () ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  ipc_lock_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_unlock_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_valid_object (TYPE_1__*) ; 
 scalar_t__ is_file_hugepages (struct file*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rlimit (int /*<<< orphan*/ ) ; 
 int security_shm_shmctl (TYPE_1__*,int) ; 
 struct shmid_kernel* shm_obtain_object_check (struct ipc_namespace*,int) ; 
 int shmem_lock (struct file*,int,struct user_struct*) ; 
 int /*<<< orphan*/  shmem_unlock_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shmctl_do_lock(struct ipc_namespace *ns, int shmid, int cmd)
{
	struct shmid_kernel *shp;
	struct file *shm_file;
	int err;

	rcu_read_lock();
	shp = shm_obtain_object_check(ns, shmid);
	if (IS_ERR(shp)) {
		err = PTR_ERR(shp);
		goto out_unlock1;
	}

	audit_ipc_obj(&(shp->shm_perm));
	err = security_shm_shmctl(&shp->shm_perm, cmd);
	if (err)
		goto out_unlock1;

	ipc_lock_object(&shp->shm_perm);

	/* check if shm_destroy() is tearing down shp */
	if (!ipc_valid_object(&shp->shm_perm)) {
		err = -EIDRM;
		goto out_unlock0;
	}

	if (!ns_capable(ns->user_ns, CAP_IPC_LOCK)) {
		kuid_t euid = current_euid();

		if (!uid_eq(euid, shp->shm_perm.uid) &&
		    !uid_eq(euid, shp->shm_perm.cuid)) {
			err = -EPERM;
			goto out_unlock0;
		}
		if (cmd == SHM_LOCK && !rlimit(RLIMIT_MEMLOCK)) {
			err = -EPERM;
			goto out_unlock0;
		}
	}

	shm_file = shp->shm_file;
	if (is_file_hugepages(shm_file))
		goto out_unlock0;

	if (cmd == SHM_LOCK) {
		struct user_struct *user = current_user();

		err = shmem_lock(shm_file, 1, user);
		if (!err && !(shp->shm_perm.mode & SHM_LOCKED)) {
			shp->shm_perm.mode |= SHM_LOCKED;
			shp->mlock_user = user;
		}
		goto out_unlock0;
	}

	/* SHM_UNLOCK */
	if (!(shp->shm_perm.mode & SHM_LOCKED))
		goto out_unlock0;
	shmem_lock(shm_file, 0, shp->mlock_user);
	shp->shm_perm.mode &= ~SHM_LOCKED;
	shp->mlock_user = NULL;
	get_file(shm_file);
	ipc_unlock_object(&shp->shm_perm);
	rcu_read_unlock();
	shmem_unlock_mapping(shm_file->f_mapping);

	fput(shm_file);
	return err;

out_unlock0:
	ipc_unlock_object(&shp->shm_perm);
out_unlock1:
	rcu_read_unlock();
	return err;
}