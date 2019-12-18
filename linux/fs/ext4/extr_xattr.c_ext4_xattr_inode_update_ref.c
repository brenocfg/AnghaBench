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
struct mb_cache {int dummy; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_ino; } ;
struct ext4_iloc {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 struct mb_cache* EA_INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int ext4_mark_iloc_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_reserve_inode_write (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_warning_inode (struct inode*,char*,int) ; 
 int /*<<< orphan*/  ext4_xattr_inode_get_hash (struct inode*) ; 
 int ext4_xattr_inode_get_ref (struct inode*) ; 
 int /*<<< orphan*/  ext4_xattr_inode_set_ref (struct inode*,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mb_cache_entry_create (struct mb_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb_cache_entry_delete (struct mb_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static int ext4_xattr_inode_update_ref(handle_t *handle, struct inode *ea_inode,
				       int ref_change)
{
	struct mb_cache *ea_inode_cache = EA_INODE_CACHE(ea_inode);
	struct ext4_iloc iloc;
	s64 ref_count;
	u32 hash;
	int ret;

	inode_lock(ea_inode);

	ret = ext4_reserve_inode_write(handle, ea_inode, &iloc);
	if (ret)
		goto out;

	ref_count = ext4_xattr_inode_get_ref(ea_inode);
	ref_count += ref_change;
	ext4_xattr_inode_set_ref(ea_inode, ref_count);

	if (ref_change > 0) {
		WARN_ONCE(ref_count <= 0, "EA inode %lu ref_count=%lld",
			  ea_inode->i_ino, ref_count);

		if (ref_count == 1) {
			WARN_ONCE(ea_inode->i_nlink, "EA inode %lu i_nlink=%u",
				  ea_inode->i_ino, ea_inode->i_nlink);

			set_nlink(ea_inode, 1);
			ext4_orphan_del(handle, ea_inode);

			if (ea_inode_cache) {
				hash = ext4_xattr_inode_get_hash(ea_inode);
				mb_cache_entry_create(ea_inode_cache,
						      GFP_NOFS, hash,
						      ea_inode->i_ino,
						      true /* reusable */);
			}
		}
	} else {
		WARN_ONCE(ref_count < 0, "EA inode %lu ref_count=%lld",
			  ea_inode->i_ino, ref_count);

		if (ref_count == 0) {
			WARN_ONCE(ea_inode->i_nlink != 1,
				  "EA inode %lu i_nlink=%u",
				  ea_inode->i_ino, ea_inode->i_nlink);

			clear_nlink(ea_inode);
			ext4_orphan_add(handle, ea_inode);

			if (ea_inode_cache) {
				hash = ext4_xattr_inode_get_hash(ea_inode);
				mb_cache_entry_delete(ea_inode_cache, hash,
						      ea_inode->i_ino);
			}
		}
	}

	ret = ext4_mark_iloc_dirty(handle, ea_inode, &iloc);
	if (ret)
		ext4_warning_inode(ea_inode,
				   "ext4_mark_iloc_dirty() failed ret=%d", ret);
out:
	inode_unlock(ea_inode);
	return ret;
}