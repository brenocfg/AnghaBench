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
typedef  int /*<<< orphan*/  umode_t ;
struct win_dev {void* minor; void* major; int /*<<< orphan*/  type; } ;
struct kvec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct cifs_tcon {TYPE_3__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct cifs_open_parms {int create_options; char* path; int reconnect; struct cifs_fid* fid; int /*<<< orphan*/  disposition; int /*<<< orphan*/  desired_access; struct cifs_sb_info* cifs_sb; struct cifs_tcon* tcon; } ;
struct cifs_io_parms {int length; scalar_t__ offset; struct cifs_tcon* tcon; int /*<<< orphan*/  pid; } ;
struct cifs_fid {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_7__ {TYPE_2__* server; } ;
struct TYPE_6__ {TYPE_1__* ops; scalar_t__ oplocks; } ;
struct TYPE_5__ {int (* open ) (unsigned int,struct cifs_open_parms*,scalar_t__*,int /*<<< orphan*/ *) ;int (* sync_write ) (unsigned int,struct cifs_fid*,struct cifs_io_parms*,unsigned int*,struct kvec*,int) ;int /*<<< orphan*/  (* close ) (unsigned int,struct cifs_tcon*,struct cifs_fid*) ;} ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int CIFS_MOUNT_UNX_EMUL ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CREATE_NOT_DIR ; 
 int CREATE_OPEN_BACKUP_INTENT ; 
 int CREATE_OPTION_SPECIAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  FILE_CREATE ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ REQ_OPLOCK ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (unsigned int,struct cifs_open_parms*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int stub2 (unsigned int,struct cifs_fid*,struct cifs_io_parms*,unsigned int*,struct kvec*,int) ; 
 int stub3 (unsigned int,struct cifs_fid*,struct cifs_io_parms*,unsigned int*,struct kvec*,int) ; 
 int /*<<< orphan*/  stub4 (unsigned int,struct cifs_tcon*,struct cifs_fid*) ; 

__attribute__((used)) static int
smb2_make_node(unsigned int xid, struct inode *inode,
	       struct dentry *dentry, struct cifs_tcon *tcon,
	       char *full_path, umode_t mode, dev_t dev)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	int rc = -EPERM;
	int create_options = CREATE_NOT_DIR | CREATE_OPTION_SPECIAL;
	FILE_ALL_INFO *buf = NULL;
	struct cifs_io_parms io_parms;
	__u32 oplock = 0;
	struct cifs_fid fid;
	struct cifs_open_parms oparms;
	unsigned int bytes_written;
	struct win_dev *pdev;
	struct kvec iov[2];

	/*
	 * Check if mounted with mount parm 'sfu' mount parm.
	 * SFU emulation should work with all servers, but only
	 * supports block and char device (no socket & fifo),
	 * and was used by default in earlier versions of Windows
	 */
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_UNX_EMUL))
		goto out;

	/*
	 * TODO: Add ability to create instead via reparse point. Windows (e.g.
	 * their current NFS server) uses this approach to expose special files
	 * over SMB2/SMB3 and Samba will do this with SMB3.1.1 POSIX Extensions
	 */

	if (!S_ISCHR(mode) && !S_ISBLK(mode))
		goto out;

	cifs_dbg(FYI, "sfu compat create special file\n");

	buf = kmalloc(sizeof(FILE_ALL_INFO), GFP_KERNEL);
	if (buf == NULL) {
		rc = -ENOMEM;
		goto out;
	}

	if (backup_cred(cifs_sb))
		create_options |= CREATE_OPEN_BACKUP_INTENT;

	oparms.tcon = tcon;
	oparms.cifs_sb = cifs_sb;
	oparms.desired_access = GENERIC_WRITE;
	oparms.create_options = create_options;
	oparms.disposition = FILE_CREATE;
	oparms.path = full_path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	if (tcon->ses->server->oplocks)
		oplock = REQ_OPLOCK;
	else
		oplock = 0;
	rc = tcon->ses->server->ops->open(xid, &oparms, &oplock, buf);
	if (rc)
		goto out;

	/*
	 * BB Do not bother to decode buf since no local inode yet to put
	 * timestamps in, but we can reuse it safely.
	 */

	pdev = (struct win_dev *)buf;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = sizeof(struct win_dev);
	iov[1].iov_base = buf;
	iov[1].iov_len = sizeof(struct win_dev);
	if (S_ISCHR(mode)) {
		memcpy(pdev->type, "IntxCHR", 8);
		pdev->major = cpu_to_le64(MAJOR(dev));
		pdev->minor = cpu_to_le64(MINOR(dev));
		rc = tcon->ses->server->ops->sync_write(xid, &fid, &io_parms,
							&bytes_written, iov, 1);
	} else if (S_ISBLK(mode)) {
		memcpy(pdev->type, "IntxBLK", 8);
		pdev->major = cpu_to_le64(MAJOR(dev));
		pdev->minor = cpu_to_le64(MINOR(dev));
		rc = tcon->ses->server->ops->sync_write(xid, &fid, &io_parms,
							&bytes_written, iov, 1);
	}
	tcon->ses->server->ops->close(xid, tcon, &fid);
	d_drop(dentry);

	/* FIXME: add code here to set EAs */
out:
	kfree(buf);
	return rc;
}