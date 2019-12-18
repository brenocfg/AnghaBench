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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_xattr_entry {int /*<<< orphan*/  e_hash; int /*<<< orphan*/  e_value_inum; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  ext4_warning_inode (struct inode*,char*,int) ; 
 int ext4_xattr_inode_dec_ref (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_xattr_inode_iget (struct inode*,unsigned int,unsigned int,struct inode**) ; 
 int ext4_xattr_inode_inc_ref (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_xattr_inode_inc_ref_all(handle_t *handle, struct inode *parent,
					struct ext4_xattr_entry *first)
{
	struct inode *ea_inode;
	struct ext4_xattr_entry *entry;
	struct ext4_xattr_entry *failed_entry;
	unsigned int ea_ino;
	int err, saved_err;

	for (entry = first; !IS_LAST_ENTRY(entry);
	     entry = EXT4_XATTR_NEXT(entry)) {
		if (!entry->e_value_inum)
			continue;
		ea_ino = le32_to_cpu(entry->e_value_inum);
		err = ext4_xattr_inode_iget(parent, ea_ino,
					    le32_to_cpu(entry->e_hash),
					    &ea_inode);
		if (err)
			goto cleanup;
		err = ext4_xattr_inode_inc_ref(handle, ea_inode);
		if (err) {
			ext4_warning_inode(ea_inode, "inc ref error %d", err);
			iput(ea_inode);
			goto cleanup;
		}
		iput(ea_inode);
	}
	return 0;

cleanup:
	saved_err = err;
	failed_entry = entry;

	for (entry = first; entry != failed_entry;
	     entry = EXT4_XATTR_NEXT(entry)) {
		if (!entry->e_value_inum)
			continue;
		ea_ino = le32_to_cpu(entry->e_value_inum);
		err = ext4_xattr_inode_iget(parent, ea_ino,
					    le32_to_cpu(entry->e_hash),
					    &ea_inode);
		if (err) {
			ext4_warning(parent->i_sb,
				     "cleanup ea_ino %u iget error %d", ea_ino,
				     err);
			continue;
		}
		err = ext4_xattr_inode_dec_ref(handle, ea_inode);
		if (err)
			ext4_warning_inode(ea_inode, "cleanup dec ref error %d",
					   err);
		iput(ea_inode);
	}
	return saved_err;
}