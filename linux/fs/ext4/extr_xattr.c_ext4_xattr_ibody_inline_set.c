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
struct inode {int dummy; } ;
struct ext4_xattr_search {int /*<<< orphan*/  first; } ;
struct ext4_xattr_info {int dummy; } ;
struct ext4_xattr_ibody_header {void* h_magic; } ;
struct ext4_xattr_ibody_find {int /*<<< orphan*/  iloc; struct ext4_xattr_search s; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ i_extra_isize; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_XATTR ; 
 int /*<<< orphan*/  EXT4_XATTR_MAGIC ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_raw_inode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_xattr_set_entry (struct ext4_xattr_info*,struct ext4_xattr_search*,int /*<<< orphan*/ *,struct inode*,int) ; 

int ext4_xattr_ibody_inline_set(handle_t *handle, struct inode *inode,
				struct ext4_xattr_info *i,
				struct ext4_xattr_ibody_find *is)
{
	struct ext4_xattr_ibody_header *header;
	struct ext4_xattr_search *s = &is->s;
	int error;

	if (EXT4_I(inode)->i_extra_isize == 0)
		return -ENOSPC;
	error = ext4_xattr_set_entry(i, s, handle, inode, false /* is_block */);
	if (error)
		return error;
	header = IHDR(inode, ext4_raw_inode(&is->iloc));
	if (!IS_LAST_ENTRY(s->first)) {
		header->h_magic = cpu_to_le32(EXT4_XATTR_MAGIC);
		ext4_set_inode_state(inode, EXT4_STATE_XATTR);
	} else {
		header->h_magic = cpu_to_le32(0);
		ext4_clear_inode_state(inode, EXT4_STATE_XATTR);
	}
	return 0;
}