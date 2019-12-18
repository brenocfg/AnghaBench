#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file_lock {int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  Capability; } ;
struct cifs_tcon {TYPE_1__ fsUnixInfo; TYPE_2__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  server; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_FILE_SB (struct file*) ; 
 int CIFS_MOUNT_NOPOSIXBRL ; 
 int CIFS_UNIX_FCNTL_CAP ; 
 int EACCES ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ IS_GETLK (int) ; 
 scalar_t__ cap_unix (TYPE_2__*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cifs_getlk (struct file*,struct file_lock*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cifs_read_flock (struct file_lock*,int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int cifs_setlk (struct file*,struct file_lock*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  free_xid (int) ; 
 int get_xid () ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

int cifs_lock(struct file *file, int cmd, struct file_lock *flock)
{
	int rc, xid;
	int lock = 0, unlock = 0;
	bool wait_flag = false;
	bool posix_lck = false;
	struct cifs_sb_info *cifs_sb;
	struct cifs_tcon *tcon;
	struct cifsFileInfo *cfile;
	__u32 type;

	rc = -EACCES;
	xid = get_xid();

	cifs_dbg(FYI, "Lock parm: 0x%x flockflags: 0x%x flocktype: 0x%x start: %lld end: %lld\n",
		 cmd, flock->fl_flags, flock->fl_type,
		 flock->fl_start, flock->fl_end);

	cfile = (struct cifsFileInfo *)file->private_data;
	tcon = tlink_tcon(cfile->tlink);

	cifs_read_flock(flock, &type, &lock, &unlock, &wait_flag,
			tcon->ses->server);
	cifs_sb = CIFS_FILE_SB(file);

	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		posix_lck = true;
	/*
	 * BB add code here to normalize offset and length to account for
	 * negative length which we can not accept over the wire.
	 */
	if (IS_GETLK(cmd)) {
		rc = cifs_getlk(file, flock, type, wait_flag, posix_lck, xid);
		free_xid(xid);
		return rc;
	}

	if (!lock && !unlock) {
		/*
		 * if no lock or unlock then nothing to do since we do not
		 * know what it is
		 */
		free_xid(xid);
		return -EOPNOTSUPP;
	}

	rc = cifs_setlk(file, flock, type, wait_flag, posix_lck, lock, unlock,
			xid);
	free_xid(xid);
	return rc;
}