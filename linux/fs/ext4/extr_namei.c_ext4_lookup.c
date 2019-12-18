#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ len; } ;
struct inode {struct inode* i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; TYPE_1__ d_name; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  inode; } ;
struct dentry {struct dentry* i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; TYPE_1__ d_name; } ;
struct buffer_head {struct buffer_head* i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; TYPE_1__ d_name; } ;
typedef  struct inode* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  EPERM ; 
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,struct inode*) ; 
 int /*<<< orphan*/  EXT4_IGET_NORMAL ; 
 scalar_t__ EXT4_NAME_LEN ; 
 scalar_t__ IS_CASEFOLDED (struct inode*) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct inode*) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 struct inode* ext4_iget (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* ext4_lookup_entry (struct inode*,struct inode*,struct ext4_dir_entry_2**) ; 
 int /*<<< orphan*/  ext4_valid_inum (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dentry *ext4_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	struct inode *inode;
	struct ext4_dir_entry_2 *de;
	struct buffer_head *bh;

	if (dentry->d_name.len > EXT4_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	bh = ext4_lookup_entry(dir, dentry, &de);
	if (IS_ERR(bh))
		return ERR_CAST(bh);
	inode = NULL;
	if (bh) {
		__u32 ino = le32_to_cpu(de->inode);
		brelse(bh);
		if (!ext4_valid_inum(dir->i_sb, ino)) {
			EXT4_ERROR_INODE(dir, "bad inode number: %u", ino);
			return ERR_PTR(-EFSCORRUPTED);
		}
		if (unlikely(ino == dir->i_ino)) {
			EXT4_ERROR_INODE(dir, "'%pd' linked to parent dir",
					 dentry);
			return ERR_PTR(-EFSCORRUPTED);
		}
		inode = ext4_iget(dir->i_sb, ino, EXT4_IGET_NORMAL);
		if (inode == ERR_PTR(-ESTALE)) {
			EXT4_ERROR_INODE(dir,
					 "deleted inode referenced: %u",
					 ino);
			return ERR_PTR(-EFSCORRUPTED);
		}
		if (!IS_ERR(inode) && IS_ENCRYPTED(dir) &&
		    (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
		    !fscrypt_has_permitted_context(dir, inode)) {
			ext4_warning(inode->i_sb,
				     "Inconsistent encryption contexts: %lu/%lu",
				     dir->i_ino, inode->i_ino);
			iput(inode);
			return ERR_PTR(-EPERM);
		}
	}

#ifdef CONFIG_UNICODE
	if (!inode && IS_CASEFOLDED(dir)) {
		/* Eventually we want to call d_add_ci(dentry, NULL)
		 * for negative dentries in the encoding case as
		 * well.  For now, prevent the negative dentry
		 * from being cached.
		 */
		return NULL;
	}
#endif
	return d_splice_alias(inode, dentry);
}