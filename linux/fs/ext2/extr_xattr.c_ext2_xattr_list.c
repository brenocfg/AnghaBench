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
struct xattr_handler {char* name; int /*<<< orphan*/  prefix; scalar_t__ (* list ) (struct dentry*) ;} ;
struct mb_cache {int dummy; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct ext2_xattr_entry {size_t e_name_len; char const* e_name; int /*<<< orphan*/  e_name_index; } ;
struct dentry {int dummy; } ;
struct buffer_head {char* b_data; int b_size; int /*<<< orphan*/  b_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  i_file_acl; } ;
struct TYPE_7__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 struct mb_cache* EA_BLOCK_CACHE (struct inode*) ; 
 int EIO ; 
 int ERANGE ; 
 TYPE_5__* EXT2_I (struct inode*) ; 
 struct ext2_xattr_entry* EXT2_XATTR_NEXT (struct ext2_xattr_entry*) ; 
 struct ext2_xattr_entry* FIRST_ENTRY (struct buffer_head*) ; 
 TYPE_2__* HDR (struct buffer_head*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext2_xattr_entry*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,...) ; 
 int /*<<< orphan*/  ext2_error (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2_xattr_cache_insert (struct mb_cache*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext2_xattr_entry_valid (struct ext2_xattr_entry*,char*,int /*<<< orphan*/ ) ; 
 struct xattr_handler* ext2_xattr_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_xattr_header_valid (TYPE_2__*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 struct buffer_head* sb_bread (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ stub1 (struct dentry*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ext2_xattr_list(struct dentry *dentry, char *buffer, size_t buffer_size)
{
	struct inode *inode = d_inode(dentry);
	struct buffer_head *bh = NULL;
	struct ext2_xattr_entry *entry;
	char *end;
	size_t rest = buffer_size;
	int error;
	struct mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (long)buffer_size);

	down_read(&EXT2_I(inode)->xattr_sem);
	error = 0;
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
		ext2_error(inode->i_sb, "ext2_xattr_list",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}

	/* check the on-disk data structure */
	entry = FIRST_ENTRY(bh);
	while (!IS_LAST_ENTRY(entry)) {
		if (!ext2_xattr_entry_valid(entry, end,
		    inode->i_sb->s_blocksize))
			goto bad_block;
		entry = EXT2_XATTR_NEXT(entry);
	}
	if (ext2_xattr_cache_insert(ea_block_cache, bh))
		ea_idebug(inode, "cache insert failed");

	/* list the attribute names */
	for (entry = FIRST_ENTRY(bh); !IS_LAST_ENTRY(entry);
	     entry = EXT2_XATTR_NEXT(entry)) {
		const struct xattr_handler *handler =
			ext2_xattr_handler(entry->e_name_index);

		if (handler && (!handler->list || handler->list(dentry))) {
			const char *prefix = handler->prefix ?: handler->name;
			size_t prefix_len = strlen(prefix);
			size_t size = prefix_len + entry->e_name_len + 1;

			if (buffer) {
				if (size > rest) {
					error = -ERANGE;
					goto cleanup;
				}
				memcpy(buffer, prefix, prefix_len);
				buffer += prefix_len;
				memcpy(buffer, entry->e_name, entry->e_name_len);
				buffer += entry->e_name_len;
				*buffer++ = 0;
			}
			rest -= size;
		}
	}
	error = buffer_size - rest;  /* total size */

cleanup:
	brelse(bh);
	up_read(&EXT2_I(inode)->xattr_sem);

	return error;
}