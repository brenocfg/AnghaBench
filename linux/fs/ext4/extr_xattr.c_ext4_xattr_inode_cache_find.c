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
typedef  int /*<<< orphan*/  u32 ;
struct mb_cache_entry {int /*<<< orphan*/  e_value; } ;
struct mb_cache {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 struct mb_cache* EA_INODE_CACHE (struct inode*) ; 
 int EXT4_EA_INODE_FL ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_IGET_NORMAL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 struct inode* ext4_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ext4_kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_inode_read (struct inode*,void*,size_t) ; 
 int /*<<< orphan*/  ext4_xattr_inode_verify_hashes (struct inode*,int /*<<< orphan*/ *,void*,size_t) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 struct mb_cache_entry* mb_cache_entry_find_first (struct mb_cache*,int /*<<< orphan*/ ) ; 
 struct mb_cache_entry* mb_cache_entry_find_next (struct mb_cache*,struct mb_cache_entry*) ; 
 int /*<<< orphan*/  mb_cache_entry_put (struct mb_cache*,struct mb_cache_entry*) ; 
 int /*<<< orphan*/  mb_cache_entry_touch (struct mb_cache*,struct mb_cache_entry*) ; 
 int /*<<< orphan*/  memcmp (void const*,void*,size_t) ; 

__attribute__((used)) static struct inode *
ext4_xattr_inode_cache_find(struct inode *inode, const void *value,
			    size_t value_len, u32 hash)
{
	struct inode *ea_inode;
	struct mb_cache_entry *ce;
	struct mb_cache *ea_inode_cache = EA_INODE_CACHE(inode);
	void *ea_data;

	if (!ea_inode_cache)
		return NULL;

	ce = mb_cache_entry_find_first(ea_inode_cache, hash);
	if (!ce)
		return NULL;

	ea_data = ext4_kvmalloc(value_len, GFP_NOFS);
	if (!ea_data) {
		mb_cache_entry_put(ea_inode_cache, ce);
		return NULL;
	}

	while (ce) {
		ea_inode = ext4_iget(inode->i_sb, ce->e_value,
				     EXT4_IGET_NORMAL);
		if (!IS_ERR(ea_inode) &&
		    !is_bad_inode(ea_inode) &&
		    (EXT4_I(ea_inode)->i_flags & EXT4_EA_INODE_FL) &&
		    i_size_read(ea_inode) == value_len &&
		    !ext4_xattr_inode_read(ea_inode, ea_data, value_len) &&
		    !ext4_xattr_inode_verify_hashes(ea_inode, NULL, ea_data,
						    value_len) &&
		    !memcmp(value, ea_data, value_len)) {
			mb_cache_entry_touch(ea_inode_cache, ce);
			mb_cache_entry_put(ea_inode_cache, ce);
			kvfree(ea_data);
			return ea_inode;
		}

		if (!IS_ERR(ea_inode))
			iput(ea_inode);
		ce = mb_cache_entry_find_next(ea_inode_cache, ce);
	}
	kvfree(ea_data);
	return NULL;
}