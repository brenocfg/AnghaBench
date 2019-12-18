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
typedef  int u16 ;
struct mb_cache {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_offs; scalar_t__ e_value_inum; int /*<<< orphan*/  e_value_size; } ;
struct buffer_head {int b_size; void* b_data; int /*<<< orphan*/  b_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_3__ {scalar_t__ i_file_acl; } ;

/* Variables and functions */
 struct ext4_xattr_entry* BFIRST (struct buffer_head*) ; 
 TYPE_2__* BHDR (struct buffer_head*) ; 
 struct mb_cache* EA_BLOCK_CACHE (struct inode*) ; 
 int ENODATA ; 
 int ERANGE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 size_t EXT4_XATTR_SIZE_MAX ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  REQ_PRIO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,unsigned long long,...) ; 
 struct buffer_head* ext4_sb_bread (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_block_cache_insert (struct mb_cache*,struct buffer_head*) ; 
 int ext4_xattr_check_block (struct inode*,struct buffer_head*) ; 
 int ext4_xattr_inode_get (struct inode*,struct ext4_xattr_entry*,void*,size_t) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int xattr_find_entry (struct inode*,struct ext4_xattr_entry**,void*,int,char const*,int) ; 

__attribute__((used)) static int
ext4_xattr_block_get(struct inode *inode, int name_index, const char *name,
		     void *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	struct ext4_xattr_entry *entry;
	size_t size;
	void *end;
	int error;
	struct mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	ea_idebug(inode, "name=%d.%s, buffer=%p, buffer_size=%ld",
		  name_index, name, buffer, (long)buffer_size);

	if (!EXT4_I(inode)->i_file_acl)
		return -ENODATA;
	ea_idebug(inode, "reading block %llu",
		  (unsigned long long)EXT4_I(inode)->i_file_acl);
	bh = ext4_sb_bread(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
	if (IS_ERR(bh))
		return PTR_ERR(bh);
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	error = ext4_xattr_check_block(inode, bh);
	if (error)
		goto cleanup;
	ext4_xattr_block_cache_insert(ea_block_cache, bh);
	entry = BFIRST(bh);
	end = bh->b_data + bh->b_size;
	error = xattr_find_entry(inode, &entry, end, name_index, name, 1);
	if (error)
		goto cleanup;
	size = le32_to_cpu(entry->e_value_size);
	error = -ERANGE;
	if (unlikely(size > EXT4_XATTR_SIZE_MAX))
		goto cleanup;
	if (buffer) {
		if (size > buffer_size)
			goto cleanup;
		if (entry->e_value_inum) {
			error = ext4_xattr_inode_get(inode, entry, buffer,
						     size);
			if (error)
				goto cleanup;
		} else {
			u16 offset = le16_to_cpu(entry->e_value_offs);
			void *p = bh->b_data + offset;

			if (unlikely(p + size > end))
				goto cleanup;
			memcpy(buffer, p, size);
		}
	}
	error = size;

cleanup:
	brelse(bh);
	return error;
}