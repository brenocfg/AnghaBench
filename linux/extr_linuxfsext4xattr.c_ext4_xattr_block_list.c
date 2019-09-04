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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_3__ {scalar_t__ i_file_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFIRST (struct buffer_head*) ; 
 TYPE_2__* BHDR (struct buffer_head*) ; 
 int /*<<< orphan*/  EA_BLOCK_CACHE (struct inode*) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  REQ_PRIO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,...) ; 
 struct buffer_head* ext4_sb_bread (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_block_cache_insert (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ext4_xattr_check_block (struct inode*,struct buffer_head*) ; 
 int ext4_xattr_list_entries (struct dentry*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_xattr_block_list(struct dentry *dentry, char *buffer, size_t buffer_size)
{
	struct inode *inode = d_inode(dentry);
	struct buffer_head *bh = NULL;
	int error;

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (long)buffer_size);

	if (!EXT4_I(inode)->i_file_acl)
		return 0;
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
	ext4_xattr_block_cache_insert(EA_BLOCK_CACHE(inode), bh);
	error = ext4_xattr_list_entries(dentry, BFIRST(bh), buffer,
					buffer_size);
cleanup:
	brelse(bh);
	return error;
}