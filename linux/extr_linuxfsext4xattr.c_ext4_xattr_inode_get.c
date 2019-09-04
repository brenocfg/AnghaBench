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
struct mb_cache {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct ext4_xattr_entry {int /*<<< orphan*/  e_hash; int /*<<< orphan*/  e_value_inum; } ;

/* Variables and functions */
 struct mb_cache* EA_INODE_CACHE (struct inode*) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_STATE_LUSTRE_EA_INODE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_warning_inode (struct inode*,char*,...) ; 
 int /*<<< orphan*/  ext4_xattr_inode_get_hash (struct inode*) ; 
 int ext4_xattr_inode_iget (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode**) ; 
 int ext4_xattr_inode_read (struct inode*,void*,size_t) ; 
 int ext4_xattr_inode_verify_hashes (struct inode*,struct ext4_xattr_entry*,void*,size_t) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_cache_entry_create (struct mb_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ext4_xattr_inode_get(struct inode *inode, struct ext4_xattr_entry *entry,
		     void *buffer, size_t size)
{
	struct mb_cache *ea_inode_cache = EA_INODE_CACHE(inode);
	struct inode *ea_inode;
	int err;

	err = ext4_xattr_inode_iget(inode, le32_to_cpu(entry->e_value_inum),
				    le32_to_cpu(entry->e_hash), &ea_inode);
	if (err) {
		ea_inode = NULL;
		goto out;
	}

	if (i_size_read(ea_inode) != size) {
		ext4_warning_inode(ea_inode,
				   "ea_inode file size=%llu entry size=%zu",
				   i_size_read(ea_inode), size);
		err = -EFSCORRUPTED;
		goto out;
	}

	err = ext4_xattr_inode_read(ea_inode, buffer, size);
	if (err)
		goto out;

	if (!ext4_test_inode_state(ea_inode, EXT4_STATE_LUSTRE_EA_INODE)) {
		err = ext4_xattr_inode_verify_hashes(ea_inode, entry, buffer,
						     size);
		if (err) {
			ext4_warning_inode(ea_inode,
					   "EA inode hash validation failed");
			goto out;
		}

		if (ea_inode_cache)
			mb_cache_entry_create(ea_inode_cache, GFP_NOFS,
					ext4_xattr_inode_get_hash(ea_inode),
					ea_inode->i_ino, true /* reusable */);
	}
out:
	iput(ea_inode);
	return err;
}