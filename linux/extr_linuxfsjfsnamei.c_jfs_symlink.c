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
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_5__ {int /*<<< orphan*/  ixpxd; } ;
struct tblock {TYPE_1__ u; int /*<<< orphan*/  ino; int /*<<< orphan*/  xflag; } ;
struct super_block {int dummy; } ;
struct metapage {int /*<<< orphan*/  data; } ;
struct inode {int i_mode; int i_size; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; struct super_block* i_sb; TYPE_2__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_link; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_8__ {int /*<<< orphan*/  commit_mutex; int /*<<< orphan*/  mode2; int /*<<< orphan*/  i_inline; int /*<<< orphan*/  ixpxd; } ;
struct TYPE_7__ {int bsize; int l2bsize; scalar_t__ nbperpage; } ;
struct TYPE_6__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_CREATE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int /*<<< orphan*/  COMMIT_PWMAP ; 
 int EIO ; 
 int IDATASIZE ; 
 int /*<<< orphan*/  INLINEEA ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  JFS_CREATE ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 TYPE_3__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  PSIZE ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  discard_new_inode (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int dtInsert (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_metapage (struct metapage*) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int /*<<< orphan*/  free_ea_wmap (struct inode*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 struct metapage* get_metapage (struct inode*,int,int /*<<< orphan*/ ,int) ; 
 struct inode* ialloc (struct inode*,int) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  jfs_aops ; 
 int /*<<< orphan*/  jfs_fast_symlink_inode_operations ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int jfs_init_security (int /*<<< orphan*/ ,struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_symlink_inode_operations ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txBegin (struct super_block*,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtInitRoot (int /*<<< orphan*/ ,struct inode*) ; 
 int xtInsert (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtTruncate (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_symlink(struct inode *dip, struct dentry *dentry,
		const char *name)
{
	int rc;
	tid_t tid;
	ino_t ino = 0;
	struct component_name dname;
	int ssize;		/* source pathname size */
	struct btstack btstack;
	struct inode *ip = d_inode(dentry);
	s64 xlen = 0;
	int bmask = 0, xsize;
	s64 xaddr;
	struct metapage *mp;
	struct super_block *sb;
	struct tblock *tblk;

	struct inode *iplist[2];

	jfs_info("jfs_symlink: dip:0x%p name:%s", dip, name);

	rc = dquot_initialize(dip);
	if (rc)
		goto out1;

	ssize = strlen(name) + 1;

	/*
	 * search parent directory for entry/freespace
	 * (dtSearch() returns parent directory page pinned)
	 */

	if ((rc = get_UCSname(&dname, dentry)))
		goto out1;

	/*
	 * allocate on-disk/in-memory inode for symbolic link:
	 * (iAlloc() returns new, locked inode)
	 */
	ip = ialloc(dip, S_IFLNK | 0777);
	if (IS_ERR(ip)) {
		rc = PTR_ERR(ip);
		goto out2;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_security(tid, ip, dip, &dentry->d_name);
	if (rc)
		goto out3;

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	/* fix symlink access permission
	 * (dir_create() ANDs in the u.u_cmask,
	 * but symlinks really need to be 777 access)
	 */
	ip->i_mode |= 0777;

	/*
	 * write symbolic link target path name
	 */
	xtInitRoot(tid, ip);

	/*
	 * write source path name inline in on-disk inode (fast symbolic link)
	 */

	if (ssize <= IDATASIZE) {
		ip->i_op = &jfs_fast_symlink_inode_operations;

		ip->i_link = JFS_IP(ip)->i_inline;
		memcpy(ip->i_link, name, ssize);
		ip->i_size = ssize - 1;

		/*
		 * if symlink is > 128 bytes, we don't have the space to
		 * store inline extended attributes
		 */
		if (ssize > sizeof (JFS_IP(ip)->i_inline))
			JFS_IP(ip)->mode2 &= ~INLINEEA;

		jfs_info("jfs_symlink: fast symlink added  ssize:%d name:%s ",
			 ssize, name);
	}
	/*
	 * write source path name in a single extent
	 */
	else {
		jfs_info("jfs_symlink: allocate extent ip:0x%p", ip);

		ip->i_op = &jfs_symlink_inode_operations;
		inode_nohighmem(ip);
		ip->i_mapping->a_ops = &jfs_aops;

		/*
		 * even though the data of symlink object (source
		 * path name) is treated as non-journaled user data,
		 * it is read/written thru buffer cache for performance.
		 */
		sb = ip->i_sb;
		bmask = JFS_SBI(sb)->bsize - 1;
		xsize = (ssize + bmask) & ~bmask;
		xaddr = 0;
		xlen = xsize >> JFS_SBI(sb)->l2bsize;
		if ((rc = xtInsert(tid, ip, 0, 0, xlen, &xaddr, 0))) {
			txAbort(tid, 0);
			goto out3;
		}
		ip->i_size = ssize - 1;
		while (ssize) {
			/* This is kind of silly since PATH_MAX == 4K */
			int copy_size = min(ssize, PSIZE);

			mp = get_metapage(ip, xaddr, PSIZE, 1);

			if (mp == NULL) {
				xtTruncate(tid, ip, 0, COMMIT_PWMAP);
				rc = -EIO;
				txAbort(tid, 0);
				goto out3;
			}
			memcpy(mp->data, name, copy_size);
			flush_metapage(mp);
			ssize -= copy_size;
			name += copy_size;
			xaddr += JFS_SBI(sb)->nbperpage;
		}
	}

	/*
	 * create entry for symbolic link in parent directory
	 */
	rc = dtSearch(dip, &dname, &ino, &btstack, JFS_CREATE);
	if (rc == 0) {
		ino = ip->i_ino;
		rc = dtInsert(tid, dip, &dname, &ino, &btstack);
	}
	if (rc) {
		if (xlen)
			xtTruncate(tid, ip, 0, COMMIT_PWMAP);
		txAbort(tid, 0);
		/* discard new inode */
		goto out3;
	}

	mark_inode_dirty(ip);

	dip->i_ctime = dip->i_mtime = current_time(dip);
	mark_inode_dirty(dip);
	/*
	 * commit update of parent directory and link object
	 */

	iplist[0] = dip;
	iplist[1] = ip;
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
	jfs_info("jfs_symlink: rc:%d", rc);
	return rc;
}