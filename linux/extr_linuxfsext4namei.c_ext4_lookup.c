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
 int EFSCORRUPTED ; 
 int ENAMETOOLONG ; 
 int EPERM ; 
 struct inode* ERR_PTR (int) ; 
 int ESTALE ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,struct inode*) ; 
 int /*<<< orphan*/  EXT4_IGET_NORMAL ; 
 scalar_t__ EXT4_NAME_LEN ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct inode*) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 scalar_t__ ext4_encrypted_inode (struct inode*) ; 
 struct inode* ext4_find_entry (struct inode*,TYPE_1__*,struct ext4_dir_entry_2**,int /*<<< orphan*/ *) ; 
 struct inode* ext4_iget (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_valid_inum (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct inode*,struct inode*) ; 
 int fscrypt_prepare_lookup (struct inode*,struct inode*,unsigned int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dentry *ext4_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	struct inode *inode;
	struct ext4_dir_entry_2 *de;
	struct buffer_head *bh;
	int err;

	err = fscrypt_prepare_lookup(dir, dentry, flags);
	if (err)
		return ERR_PTR(err);

	if (dentry->d_name.len > EXT4_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	bh = ext4_find_entry(dir, &dentry->d_name, &de, NULL);
	if (IS_ERR(bh))
		return (struct dentry *) bh;
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
		if (!IS_ERR(inode) && ext4_encrypted_inode(dir) &&
		    (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
		    !fscrypt_has_permitted_context(dir, inode)) {
			ext4_warning(inode->i_sb,
				     "Inconsistent encryption contexts: %lu/%lu",
				     dir->i_ino, inode->i_ino);
			iput(inode);
			return ERR_PTR(-EPERM);
		}
	}
	return d_splice_alias(inode, dentry);
}