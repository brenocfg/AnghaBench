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
typedef  scalar_t__ u64 ;
struct file_lock {int fl_type; int /*<<< orphan*/  fl_owner; scalar_t__ fl_pid; scalar_t__ fl_start; scalar_t__ fl_end; } ;
struct ceph_filelock {int /*<<< orphan*/  type; void* owner; void* pid; void* client; void* length; void* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_LOCK_EXCL ; 
 int /*<<< orphan*/  CEPH_LOCK_SHARED ; 
 int /*<<< orphan*/  CEPH_LOCK_UNLOCK ; 
 int EINVAL ; 
#define  F_RDLCK 130 
#define  F_UNLCK 129 
#define  F_WRLCK 128 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dout (char*,int) ; 
 scalar_t__ secure_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lock_to_ceph_filelock(struct file_lock *lock,
				 struct ceph_filelock *cephlock)
{
	int err = 0;
	cephlock->start = cpu_to_le64(lock->fl_start);
	cephlock->length = cpu_to_le64(lock->fl_end - lock->fl_start + 1);
	cephlock->client = cpu_to_le64(0);
	cephlock->pid = cpu_to_le64((u64)lock->fl_pid);
	cephlock->owner = cpu_to_le64(secure_addr(lock->fl_owner));

	switch (lock->fl_type) {
	case F_RDLCK:
		cephlock->type = CEPH_LOCK_SHARED;
		break;
	case F_WRLCK:
		cephlock->type = CEPH_LOCK_EXCL;
		break;
	case F_UNLCK:
		cephlock->type = CEPH_LOCK_UNLOCK;
		break;
	default:
		dout("Have unknown lock type %d\n", lock->fl_type);
		err = -EINVAL;
	}

	return err;
}