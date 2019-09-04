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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_super_block {int /*<<< orphan*/  s_last_error_block; } ;
struct ext4_extent_idx {int dummy; } ;
struct ext4_extent_header {scalar_t__ eh_entries; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
struct TYPE_2__ {struct ext4_super_block* s_es; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 struct ext4_extent_idx* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_valid_extent (struct inode*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_valid_extent_idx (struct inode*,struct ext4_extent_idx*) ; 
 unsigned short le16_to_cpu (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_valid_extent_entries(struct inode *inode,
				struct ext4_extent_header *eh,
				int depth)
{
	unsigned short entries;
	if (eh->eh_entries == 0)
		return 1;

	entries = le16_to_cpu(eh->eh_entries);

	if (depth == 0) {
		/* leaf entries */
		struct ext4_extent *ext = EXT_FIRST_EXTENT(eh);
		struct ext4_super_block *es = EXT4_SB(inode->i_sb)->s_es;
		ext4_fsblk_t pblock = 0;
		ext4_lblk_t lblock = 0;
		ext4_lblk_t prev = 0;
		int len = 0;
		while (entries) {
			if (!ext4_valid_extent(inode, ext))
				return 0;

			/* Check for overlapping extents */
			lblock = le32_to_cpu(ext->ee_block);
			len = ext4_ext_get_actual_len(ext);
			if ((lblock <= prev) && prev) {
				pblock = ext4_ext_pblock(ext);
				es->s_last_error_block = cpu_to_le64(pblock);
				return 0;
			}
			ext++;
			entries--;
			prev = lblock + len - 1;
		}
	} else {
		struct ext4_extent_idx *ext_idx = EXT_FIRST_INDEX(eh);
		while (entries) {
			if (!ext4_valid_extent_idx(inode, ext_idx))
				return 0;
			ext_idx++;
			entries--;
		}
	}
	return 1;
}