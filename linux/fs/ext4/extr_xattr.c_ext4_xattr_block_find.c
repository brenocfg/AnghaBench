#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct ext4_xattr_info {int /*<<< orphan*/  name; int /*<<< orphan*/  name_index; scalar_t__ value_len; int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int not_found; scalar_t__ end; int /*<<< orphan*/  here; int /*<<< orphan*/  first; TYPE_8__* base; } ;
struct ext4_xattr_block_find {TYPE_1__ s; TYPE_2__* bh; } ;
struct TYPE_14__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_13__ {scalar_t__ i_file_acl; } ;
struct TYPE_12__ {scalar_t__ b_size; scalar_t__ b_data; int /*<<< orphan*/  b_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFIRST (TYPE_2__*) ; 
 TYPE_8__* BHDR (TYPE_2__*) ; 
 int ENODATA ; 
 TYPE_7__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  REQ_PRIO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ea_bdebug (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 TYPE_2__* ext4_sb_bread (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ext4_xattr_check_block (struct inode*,TYPE_2__*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int xattr_find_entry (struct inode*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ext4_xattr_block_find(struct inode *inode, struct ext4_xattr_info *i,
		      struct ext4_xattr_block_find *bs)
{
	struct super_block *sb = inode->i_sb;
	int error;

	ea_idebug(inode, "name=%d.%s, value=%p, value_len=%ld",
		  i->name_index, i->name, i->value, (long)i->value_len);

	if (EXT4_I(inode)->i_file_acl) {
		/* The inode already has an extended attribute block. */
		bs->bh = ext4_sb_bread(sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
		if (IS_ERR(bs->bh))
			return PTR_ERR(bs->bh);
		ea_bdebug(bs->bh, "b_count=%d, refcount=%d",
			atomic_read(&(bs->bh->b_count)),
			le32_to_cpu(BHDR(bs->bh)->h_refcount));
		error = ext4_xattr_check_block(inode, bs->bh);
		if (error)
			return error;
		/* Find the named attribute. */
		bs->s.base = BHDR(bs->bh);
		bs->s.first = BFIRST(bs->bh);
		bs->s.end = bs->bh->b_data + bs->bh->b_size;
		bs->s.here = bs->s.first;
		error = xattr_find_entry(inode, &bs->s.here, bs->s.end,
					 i->name_index, i->name, 1);
		if (error && error != -ENODATA)
			return error;
		bs->s.not_found = error;
	}
	return 0;
}