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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ EA_INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 struct inode* ext4_xattr_inode_cache_find (struct inode*,void const*,size_t,int /*<<< orphan*/ ) ; 
 struct inode* ext4_xattr_inode_create (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_inode_dec_ref (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_xattr_inode_hash (int /*<<< orphan*/ ,void const*,size_t) ; 
 int ext4_xattr_inode_inc_ref (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_xattr_inode_write (int /*<<< orphan*/ *,struct inode*,void const*,size_t) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mb_cache_entry_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ext4_xattr_inode_lookup_create(handle_t *handle, struct inode *inode,
					  const void *value, size_t value_len,
					  struct inode **ret_inode)
{
	struct inode *ea_inode;
	u32 hash;
	int err;

	hash = ext4_xattr_inode_hash(EXT4_SB(inode->i_sb), value, value_len);
	ea_inode = ext4_xattr_inode_cache_find(inode, value, value_len, hash);
	if (ea_inode) {
		err = ext4_xattr_inode_inc_ref(handle, ea_inode);
		if (err) {
			iput(ea_inode);
			return err;
		}

		*ret_inode = ea_inode;
		return 0;
	}

	/* Create an inode for the EA value */
	ea_inode = ext4_xattr_inode_create(handle, inode, hash);
	if (IS_ERR(ea_inode))
		return PTR_ERR(ea_inode);

	err = ext4_xattr_inode_write(handle, ea_inode, value, value_len);
	if (err) {
		ext4_xattr_inode_dec_ref(handle, ea_inode);
		iput(ea_inode);
		return err;
	}

	if (EA_INODE_CACHE(inode))
		mb_cache_entry_create(EA_INODE_CACHE(inode), GFP_NOFS, hash,
				      ea_inode->i_ino, true /* reusable */);

	*ret_inode = ea_inode;
	return 0;
}