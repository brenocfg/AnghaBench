#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file_lock {void* fl_type; scalar_t__ fl_start; int /*<<< orphan*/  fl_owner; scalar_t__ fl_end; } ;
struct file {scalar_t__ private_data; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct TYPE_6__ {int /*<<< orphan*/  netfid; } ;
struct cifsFileInfo {TYPE_2__ fid; int /*<<< orphan*/  tlink; } ;
struct TCP_Server_Info {TYPE_4__* vals; TYPE_3__* ops; } ;
typedef  scalar_t__ __u64 ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_8__ {int shared_lock_type; int exclusive_lock_type; } ;
struct TYPE_7__ {int (* mand_lock ) (unsigned int,struct cifsFileInfo*,scalar_t__,scalar_t__,int,int,int,int) ;} ;
struct TYPE_5__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int CIFSSMBPosixLock (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct file_lock*,int,int) ; 
 int CIFS_RDLCK ; 
 int CIFS_WRLCK ; 
 void* F_RDLCK ; 
 void* F_UNLCK ; 
 void* F_WRLCK ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int cifs_lock_test (struct cifsFileInfo*,scalar_t__,scalar_t__,int,struct file_lock*) ; 
 int cifs_posix_lock_test (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  hash_lockowner (int /*<<< orphan*/ ) ; 
 int stub1 (unsigned int,struct cifsFileInfo*,scalar_t__,scalar_t__,int,int,int,int) ; 
 int stub2 (unsigned int,struct cifsFileInfo*,scalar_t__,scalar_t__,int,int,int,int) ; 
 int stub3 (unsigned int,struct cifsFileInfo*,scalar_t__,scalar_t__,int,int,int,int) ; 
 int stub4 (unsigned int,struct cifsFileInfo*,scalar_t__,scalar_t__,int,int,int,int) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_getlk(struct file *file, struct file_lock *flock, __u32 type,
	   bool wait_flag, bool posix_lck, unsigned int xid)
{
	int rc = 0;
	__u64 length = 1 + flock->fl_end - flock->fl_start;
	struct cifsFileInfo *cfile = (struct cifsFileInfo *)file->private_data;
	struct cifs_tcon *tcon = tlink_tcon(cfile->tlink);
	struct TCP_Server_Info *server = tcon->ses->server;
	__u16 netfid = cfile->fid.netfid;

	if (posix_lck) {
		int posix_lock_type;

		rc = cifs_posix_lock_test(file, flock);
		if (!rc)
			return rc;

		if (type & server->vals->shared_lock_type)
			posix_lock_type = CIFS_RDLCK;
		else
			posix_lock_type = CIFS_WRLCK;
		rc = CIFSSMBPosixLock(xid, tcon, netfid,
				      hash_lockowner(flock->fl_owner),
				      flock->fl_start, length, flock,
				      posix_lock_type, wait_flag);
		return rc;
	}

	rc = cifs_lock_test(cfile, flock->fl_start, length, type, flock);
	if (!rc)
		return rc;

	/* BB we could chain these into one lock request BB */
	rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length, type,
				    1, 0, false);
	if (rc == 0) {
		rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
					    type, 0, 1, false);
		flock->fl_type = F_UNLCK;
		if (rc != 0)
			cifs_dbg(VFS, "Error unlocking previously locked range %d during test of lock\n",
				 rc);
		return 0;
	}

	if (type & server->vals->shared_lock_type) {
		flock->fl_type = F_WRLCK;
		return 0;
	}

	type &= ~server->vals->exclusive_lock_type;

	rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
				    type | server->vals->shared_lock_type,
				    1, 0, false);
	if (rc == 0) {
		rc = server->ops->mand_lock(xid, cfile, flock->fl_start, length,
			type | server->vals->shared_lock_type, 0, 1, false);
		flock->fl_type = F_RDLCK;
		if (rc != 0)
			cifs_dbg(VFS, "Error unlocking previously locked range %d during test of lock\n",
				 rc);
	} else
		flock->fl_type = F_WRLCK;

	return 0;
}