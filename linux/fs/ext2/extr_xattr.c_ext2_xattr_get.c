#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mb_cache {int dummy; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct ext2_xattr_entry {int /*<<< orphan*/  e_value_offs; int /*<<< orphan*/  e_value_size; } ;
struct buffer_head {char* b_data; int b_size; int /*<<< orphan*/  b_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  i_file_acl; } ;
struct TYPE_7__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 struct mb_cache* EA_BLOCK_CACHE (struct inode*) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODATA ; 
 int ERANGE ; 
 TYPE_5__* EXT2_I (struct inode*) ; 
 struct ext2_xattr_entry* EXT2_XATTR_NEXT (struct ext2_xattr_entry*) ; 
 struct ext2_xattr_entry* FIRST_ENTRY (struct buffer_head*) ; 
 TYPE_2__* HDR (struct buffer_head*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext2_xattr_entry*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,...) ; 
 int /*<<< orphan*/  ext2_error (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2_xattr_cache_insert (struct mb_cache*,struct buffer_head*) ; 
 int ext2_xattr_cmp_entry (int,size_t,char const*,struct ext2_xattr_entry*) ; 
 int /*<<< orphan*/  ext2_xattr_entry_valid (struct ext2_xattr_entry*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_xattr_header_valid (TYPE_2__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 struct buffer_head* sb_bread (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int
ext2_xattr_get(struct inode *inode, int name_index, const char *name,
	       void *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	struct ext2_xattr_entry *entry;
	size_t name_len, size;
	char *end;
	int error, not_found;
	struct mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	ea_idebug(inode, "name=%d.%s, buffer=%p, buffer_size=%ld",
		  name_index, name, buffer, (long)buffer_size);

	if (name == NULL)
		return -EINVAL;
	name_len = strlen(name);
	if (name_len > 255)
		return -ERANGE;

	down_read(&EXT2_I(inode)->xattr_sem);
	error = -ENODATA;
	if (!EXT2_I(inode)->i_file_acl)
		goto cleanup;
	ea_idebug(inode, "reading block %d", EXT2_I(inode)->i_file_acl);
	bh = sb_bread(inode->i_sb, EXT2_I(inode)->i_file_acl);
	error = -EIO;
	if (!bh)
		goto cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(HDR(bh)->h_refcount));
	end = bh->b_data + bh->b_size;
	if (!ext2_xattr_header_valid(HDR(bh))) {
bad_block:
		ext2_error(inode->i_sb, "ext2_xattr_get",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}

	/* find named attribute */
	entry = FIRST_ENTRY(bh);
	while (!IS_LAST_ENTRY(entry)) {
		if (!ext2_xattr_entry_valid(entry, end,
		    inode->i_sb->s_blocksize))
			goto bad_block;

		not_found = ext2_xattr_cmp_entry(name_index, name_len, name,
						 entry);
		if (!not_found)
			goto found;
		if (not_found < 0)
			break;

		entry = EXT2_XATTR_NEXT(entry);
	}
	if (ext2_xattr_cache_insert(ea_block_cache, bh))
		ea_idebug(inode, "cache insert failed");
	error = -ENODATA;
	goto cleanup;
found:
	size = le32_to_cpu(entry->e_value_size);
	if (ext2_xattr_cache_insert(ea_block_cache, bh))
		ea_idebug(inode, "cache insert failed");
	if (buffer) {
		error = -ERANGE;
		if (size > buffer_size)
			goto cleanup;
		/* return value of attribute */
		memcpy(buffer, bh->b_data + le16_to_cpu(entry->e_value_offs),
			size);
	}
	error = size;

cleanup:
	brelse(bh);
	up_read(&EXT2_I(inode)->xattr_sem);

	return error;
}