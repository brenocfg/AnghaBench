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
struct superblock_smack {struct smack_known* smk_root; struct smack_known* smk_default; } ;
struct super_block {int s_magic; struct superblock_smack* s_security; } ;
struct smack_known {int dummy; } ;
struct inode_smack {int smk_flags; int /*<<< orphan*/  smk_lock; struct smack_known* smk_inode; struct smack_known* smk_mmap; struct smack_known* smk_task; } ;
struct inode {int i_opflags; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
#define  CGROUP2_SUPER_MAGIC 135 
#define  CGROUP_SUPER_MAGIC 134 
#define  DEVPTS_SUPER_MAGIC 133 
 int EINVAL ; 
 int IOP_XATTR ; 
 int /*<<< orphan*/  IS_ERR (struct smack_known*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct smack_known*) ; 
#define  PIPEFS_MAGIC 132 
#define  PROC_SUPER_MAGIC 131 
#define  SMACK_MAGIC 130 
 int SMK_INODE_CHANGED ; 
 int SMK_INODE_INSTANT ; 
 int SMK_INODE_TRANSMUTE ; 
#define  SOCKFS_MAGIC 129 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
#define  TMPFS_MAGIC 128 
 int /*<<< orphan*/  TRANS_TRUE ; 
 int TRANS_TRUE_SIZE ; 
 int /*<<< orphan*/  XATTR_NAME_SMACK ; 
 int /*<<< orphan*/  XATTR_NAME_SMACKEXEC ; 
 int /*<<< orphan*/  XATTR_NAME_SMACKMMAP ; 
 int /*<<< orphan*/  XATTR_NAME_SMACKTRANSMUTE ; 
 int __vfs_getxattr (struct dentry*,struct inode*,int /*<<< orphan*/ ,char*,int) ; 
 int __vfs_setxattr (struct dentry*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode_smack* smack_inode (struct inode*) ; 
 struct smack_known smack_known_star ; 
 struct smack_known smack_known_web ; 
 struct smack_known* smk_fetch (int /*<<< orphan*/ ,struct inode*,struct dentry*) ; 
 void* smk_of_current () ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smack_d_instantiate(struct dentry *opt_dentry, struct inode *inode)
{
	struct super_block *sbp;
	struct superblock_smack *sbsp;
	struct inode_smack *isp;
	struct smack_known *skp;
	struct smack_known *ckp = smk_of_current();
	struct smack_known *final;
	char trattr[TRANS_TRUE_SIZE];
	int transflag = 0;
	int rc;
	struct dentry *dp;

	if (inode == NULL)
		return;

	isp = smack_inode(inode);

	mutex_lock(&isp->smk_lock);
	/*
	 * If the inode is already instantiated
	 * take the quick way out
	 */
	if (isp->smk_flags & SMK_INODE_INSTANT)
		goto unlockandout;

	sbp = inode->i_sb;
	sbsp = sbp->s_security;
	/*
	 * We're going to use the superblock default label
	 * if there's no label on the file.
	 */
	final = sbsp->smk_default;

	/*
	 * If this is the root inode the superblock
	 * may be in the process of initialization.
	 * If that is the case use the root value out
	 * of the superblock.
	 */
	if (opt_dentry->d_parent == opt_dentry) {
		switch (sbp->s_magic) {
		case CGROUP_SUPER_MAGIC:
		case CGROUP2_SUPER_MAGIC:
			/*
			 * The cgroup filesystem is never mounted,
			 * so there's no opportunity to set the mount
			 * options.
			 */
			sbsp->smk_root = &smack_known_star;
			sbsp->smk_default = &smack_known_star;
			isp->smk_inode = sbsp->smk_root;
			break;
		case TMPFS_MAGIC:
			/*
			 * What about shmem/tmpfs anonymous files with dentry
			 * obtained from d_alloc_pseudo()?
			 */
			isp->smk_inode = smk_of_current();
			break;
		case PIPEFS_MAGIC:
			isp->smk_inode = smk_of_current();
			break;
		case SOCKFS_MAGIC:
			/*
			 * Socket access is controlled by the socket
			 * structures associated with the task involved.
			 */
			isp->smk_inode = &smack_known_star;
			break;
		default:
			isp->smk_inode = sbsp->smk_root;
			break;
		}
		isp->smk_flags |= SMK_INODE_INSTANT;
		goto unlockandout;
	}

	/*
	 * This is pretty hackish.
	 * Casey says that we shouldn't have to do
	 * file system specific code, but it does help
	 * with keeping it simple.
	 */
	switch (sbp->s_magic) {
	case SMACK_MAGIC:
	case CGROUP_SUPER_MAGIC:
	case CGROUP2_SUPER_MAGIC:
		/*
		 * Casey says that it's a little embarrassing
		 * that the smack file system doesn't do
		 * extended attributes.
		 *
		 * Cgroupfs is special
		 */
		final = &smack_known_star;
		break;
	case DEVPTS_SUPER_MAGIC:
		/*
		 * devpts seems content with the label of the task.
		 * Programs that change smack have to treat the
		 * pty with respect.
		 */
		final = ckp;
		break;
	case PROC_SUPER_MAGIC:
		/*
		 * Casey says procfs appears not to care.
		 * The superblock default suffices.
		 */
		break;
	case TMPFS_MAGIC:
		/*
		 * Device labels should come from the filesystem,
		 * but watch out, because they're volitile,
		 * getting recreated on every reboot.
		 */
		final = &smack_known_star;
		/*
		 * If a smack value has been set we want to use it,
		 * but since tmpfs isn't giving us the opportunity
		 * to set mount options simulate setting the
		 * superblock default.
		 */
		/* Fall through */
	default:
		/*
		 * This isn't an understood special case.
		 * Get the value from the xattr.
		 */

		/*
		 * UNIX domain sockets use lower level socket data.
		 */
		if (S_ISSOCK(inode->i_mode)) {
			final = &smack_known_star;
			break;
		}
		/*
		 * No xattr support means, alas, no SMACK label.
		 * Use the aforeapplied default.
		 * It would be curious if the label of the task
		 * does not match that assigned.
		 */
		if (!(inode->i_opflags & IOP_XATTR))
		        break;
		/*
		 * Get the dentry for xattr.
		 */
		dp = dget(opt_dentry);
		skp = smk_fetch(XATTR_NAME_SMACK, inode, dp);
		if (!IS_ERR_OR_NULL(skp))
			final = skp;

		/*
		 * Transmuting directory
		 */
		if (S_ISDIR(inode->i_mode)) {
			/*
			 * If this is a new directory and the label was
			 * transmuted when the inode was initialized
			 * set the transmute attribute on the directory
			 * and mark the inode.
			 *
			 * If there is a transmute attribute on the
			 * directory mark the inode.
			 */
			if (isp->smk_flags & SMK_INODE_CHANGED) {
				isp->smk_flags &= ~SMK_INODE_CHANGED;
				rc = __vfs_setxattr(dp, inode,
					XATTR_NAME_SMACKTRANSMUTE,
					TRANS_TRUE, TRANS_TRUE_SIZE,
					0);
			} else {
				rc = __vfs_getxattr(dp, inode,
					XATTR_NAME_SMACKTRANSMUTE, trattr,
					TRANS_TRUE_SIZE);
				if (rc >= 0 && strncmp(trattr, TRANS_TRUE,
						       TRANS_TRUE_SIZE) != 0)
					rc = -EINVAL;
			}
			if (rc >= 0)
				transflag = SMK_INODE_TRANSMUTE;
		}
		/*
		 * Don't let the exec or mmap label be "*" or "@".
		 */
		skp = smk_fetch(XATTR_NAME_SMACKEXEC, inode, dp);
		if (IS_ERR(skp) || skp == &smack_known_star ||
		    skp == &smack_known_web)
			skp = NULL;
		isp->smk_task = skp;

		skp = smk_fetch(XATTR_NAME_SMACKMMAP, inode, dp);
		if (IS_ERR(skp) || skp == &smack_known_star ||
		    skp == &smack_known_web)
			skp = NULL;
		isp->smk_mmap = skp;

		dput(dp);
		break;
	}

	if (final == NULL)
		isp->smk_inode = ckp;
	else
		isp->smk_inode = final;

	isp->smk_flags |= (SMK_INODE_INSTANT | transflag);

unlockandout:
	mutex_unlock(&isp->smk_lock);
	return;
}