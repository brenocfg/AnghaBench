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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_3__ {int /*<<< orphan*/  ixpxd; } ;
struct tblock {TYPE_1__ u; int /*<<< orphan*/  ino; int /*<<< orphan*/  xflag; } ;
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; int /*<<< orphan*/  ixpxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_CREATE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  JFS_CREATE ; 
 TYPE_2__* JFS_IP (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  discard_new_inode (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  dtInitRoot (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int dtInsert (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int /*<<< orphan*/  free_ea_wmap (struct inode*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 struct inode* ialloc (struct inode*,int) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  jfs_dir_inode_operations ; 
 int /*<<< orphan*/  jfs_dir_operations ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int jfs_init_acl (int /*<<< orphan*/ ,struct inode*,struct inode*) ; 
 int jfs_init_security (int /*<<< orphan*/ ,struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_mkdir(struct inode *dip, struct dentry *dentry, umode_t mode)
{
	int rc = 0;
	tid_t tid;		/* transaction id */
	struct inode *ip = NULL;	/* child directory inode */
	ino_t ino;
	struct component_name dname;	/* child directory name */
	struct btstack btstack;
	struct inode *iplist[2];
	struct tblock *tblk;

	jfs_info("jfs_mkdir: dip:0x%p name:%pd", dip, dentry);

	rc = dquot_initialize(dip);
	if (rc)
		goto out1;

	/*
	 * search parent directory for entry/freespace
	 * (dtSearch() returns parent directory page pinned)
	 */
	if ((rc = get_UCSname(&dname, dentry)))
		goto out1;

	/*
	 * Either iAlloc() or txBegin() may block.  Deadlock can occur if we
	 * block there while holding dtree page, so we allocate the inode &
	 * begin the transaction before we search the directory.
	 */
	ip = ialloc(dip, S_IFDIR | mode);
	if (IS_ERR(ip)) {
		rc = PTR_ERR(ip);
		goto out2;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_acl(tid, ip, dip);
	if (rc)
		goto out3;

	rc = jfs_init_security(tid, ip, dip, &dentry->d_name);
	if (rc) {
		txAbort(tid, 0);
		goto out3;
	}

	if ((rc = dtSearch(dip, &dname, &ino, &btstack, JFS_CREATE))) {
		jfs_err("jfs_mkdir: dtSearch returned %d", rc);
		txAbort(tid, 0);
		goto out3;
	}

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	iplist[0] = dip;
	iplist[1] = ip;

	/*
	 * initialize the child directory in-line in inode
	 */
	dtInitRoot(tid, ip, dip->i_ino);

	/*
	 * create entry in parent directory for child directory
	 * (dtInsert() releases parent directory page)
	 */
	ino = ip->i_ino;
	if ((rc = dtInsert(tid, dip, &dname, &ino, &btstack))) {
		if (rc == -EIO) {
			jfs_err("jfs_mkdir: dtInsert returned -EIO");
			txAbort(tid, 1);	/* Marks Filesystem dirty */
		} else
			txAbort(tid, 0);	/* Filesystem full */
		goto out3;
	}

	set_nlink(ip, 2);	/* for '.' */
	ip->i_op = &jfs_dir_inode_operations;
	ip->i_fop = &jfs_dir_operations;

	mark_inode_dirty(ip);

	/* update parent directory inode */
	inc_nlink(dip);		/* for '..' from child directory */
	dip->i_ctime = dip->i_mtime = current_time(dip);
	mark_inode_dirty(dip);

	rc = txCommit(tid, 2, &iplist[0], 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);
	if (rc) {
		free_ea_wmap(ip);
		clear_nlink(ip);
		discard_new_inode(ip);
	} else {
		d_instantiate_new(dentry, ip);
	}

      out2:
	free_UCSname(&dname);


      out1:

	jfs_info("jfs_mkdir: rc:%d", rc);
	return rc;
}