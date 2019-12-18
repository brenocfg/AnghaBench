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
struct ext4_xattr_ibody_header {int dummy; } ;
struct ext4_xattr_entry {scalar_t__ e_value_size; int /*<<< orphan*/  e_value_offs; int /*<<< orphan*/  e_value_inum; } ;
struct ext4_inode {int dummy; } ;
struct ext4_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int i_extra_isize; int i_inline_off; } ;
struct TYPE_3__ {int s_inode_size; } ;

/* Variables and functions */
 int EXT4_GOOD_OLD_INODE_SIZE ; 
 TYPE_2__* EXT4_I (struct inode*) ; 
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_STATE_XATTR ; 
 int EXT4_XATTR_LEN (int /*<<< orphan*/ ) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 int EXT4_XATTR_ROUND ; 
 int EXT4_XATTR_SIZE (int) ; 
 int /*<<< orphan*/  EXT4_XATTR_SYSTEM_DATA ; 
 struct ext4_xattr_entry* IFIRST (struct ext4_xattr_ibody_header*) ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,struct ext4_inode*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 struct ext4_inode* ext4_raw_inode (struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_max_inline_xattr_value_size(struct inode *inode,
					   struct ext4_iloc *iloc)
{
	struct ext4_xattr_ibody_header *header;
	struct ext4_xattr_entry *entry;
	struct ext4_inode *raw_inode;
	int free, min_offs;

	min_offs = EXT4_SB(inode->i_sb)->s_inode_size -
			EXT4_GOOD_OLD_INODE_SIZE -
			EXT4_I(inode)->i_extra_isize -
			sizeof(struct ext4_xattr_ibody_header);

	/*
	 * We need to subtract another sizeof(__u32) since an in-inode xattr
	 * needs an empty 4 bytes to indicate the gap between the xattr entry
	 * and the name/value pair.
	 */
	if (!ext4_test_inode_state(inode, EXT4_STATE_XATTR))
		return EXT4_XATTR_SIZE(min_offs -
			EXT4_XATTR_LEN(strlen(EXT4_XATTR_SYSTEM_DATA)) -
			EXT4_XATTR_ROUND - sizeof(__u32));

	raw_inode = ext4_raw_inode(iloc);
	header = IHDR(inode, raw_inode);
	entry = IFIRST(header);

	/* Compute min_offs. */
	for (; !IS_LAST_ENTRY(entry); entry = EXT4_XATTR_NEXT(entry)) {
		if (!entry->e_value_inum && entry->e_value_size) {
			size_t offs = le16_to_cpu(entry->e_value_offs);
			if (offs < min_offs)
				min_offs = offs;
		}
	}
	free = min_offs -
		((void *)entry - (void *)IFIRST(header)) - sizeof(__u32);

	if (EXT4_I(inode)->i_inline_off) {
		entry = (struct ext4_xattr_entry *)
			((void *)raw_inode + EXT4_I(inode)->i_inline_off);

		free += EXT4_XATTR_SIZE(le32_to_cpu(entry->e_value_size));
		goto out;
	}

	free -= EXT4_XATTR_LEN(strlen(EXT4_XATTR_SYSTEM_DATA));

	if (free > EXT4_XATTR_ROUND)
		free = EXT4_XATTR_SIZE(free - EXT4_XATTR_ROUND);
	else
		free = 0;

out:
	return free;
}