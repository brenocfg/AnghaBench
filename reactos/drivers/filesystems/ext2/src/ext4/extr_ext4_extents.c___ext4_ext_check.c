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
struct inode {int dummy; } ;
struct ext4_extent_tail {scalar_t__ et_checksum; } ;
struct ext4_extent_header {scalar_t__ eh_magic; scalar_t__ eh_max; scalar_t__ eh_entries; int /*<<< orphan*/  eh_depth; } ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ EXT4_EXT_MAGIC ; 
 scalar_t__ ext4_ext_block_csum (struct inode*,struct ext4_extent_header*) ; 
 int /*<<< orphan*/  ext_debug (char*,char const*,...) ; 
 struct ext4_extent_tail* find_ext4_extent_tail (struct ext4_extent_header*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ext4_ext_check(const char *function, unsigned int line,
		struct inode *inode,
		struct ext4_extent_header *eh, int depth,
		ext4_fsblk_t pblk)
{
	struct ext4_extent_tail *tail;
	const char *error_msg;
#ifndef __REACTOS__
	int max = 0;
#endif
	if (eh->eh_magic != EXT4_EXT_MAGIC) {
		error_msg = "invalid magic";
		goto corrupted;
	}
	if (le16_to_cpu(eh->eh_depth) != depth) {
		error_msg = "unexpected eh_depth";
		goto corrupted;
	}
	if (eh->eh_max == 0) {
		error_msg = "invalid eh_max";
		goto corrupted;
	}
	if (eh->eh_entries > eh->eh_max) {
		error_msg = "invalid eh_entries";
		goto corrupted;
	}

	tail = find_ext4_extent_tail(eh);
	if (tail->et_checksum != ext4_ext_block_csum(inode, eh)) {
		ext_debug("Warning: extent checksum damaged? tail->et_checksum = "
				"%lu, ext4_ext_block_csum = %lu\n",
				tail->et_checksum, ext4_ext_block_csum(inode, eh));
	}

	return 0;

corrupted:
	ext_debug("corrupted! %s\n", error_msg);
	return -EIO;
}