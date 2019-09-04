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
struct ext4_dir_entry {int dummy; } ;
struct dx_tail {scalar_t__ dt_checksum; } ;
struct dx_entry {int dummy; } ;
struct dx_countlimit {int /*<<< orphan*/  count; int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int EXT4_BLOCK_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*) ; 
 scalar_t__ ext4_dx_csum (struct inode*,struct ext4_dir_entry*,int,int,struct dx_tail*) ; 
 int /*<<< orphan*/  ext4_has_metadata_csum (int /*<<< orphan*/ ) ; 
 struct dx_countlimit* get_dx_countlimit (struct inode*,struct ext4_dir_entry*,int*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_no_space_for_csum (struct inode*) ; 

__attribute__((used)) static int ext4_dx_csum_verify(struct inode *inode,
			       struct ext4_dir_entry *dirent)
{
	struct dx_countlimit *c;
	struct dx_tail *t;
	int count_offset, limit, count;

	if (!ext4_has_metadata_csum(inode->i_sb))
		return 1;

	c = get_dx_countlimit(inode, dirent, &count_offset);
	if (!c) {
		EXT4_ERROR_INODE(inode, "dir seems corrupt?  Run e2fsck -D.");
		return 0;
	}
	limit = le16_to_cpu(c->limit);
	count = le16_to_cpu(c->count);
	if (count_offset + (limit * sizeof(struct dx_entry)) >
	    EXT4_BLOCK_SIZE(inode->i_sb) - sizeof(struct dx_tail)) {
		warn_no_space_for_csum(inode);
		return 0;
	}
	t = (struct dx_tail *)(((struct dx_entry *)c) + limit);

	if (t->dt_checksum != ext4_dx_csum(inode, dirent, count_offset,
					    count, t))
		return 0;
	return 1;
}