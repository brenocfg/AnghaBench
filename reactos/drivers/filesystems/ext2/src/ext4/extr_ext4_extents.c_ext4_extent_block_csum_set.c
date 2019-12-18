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
struct ext4_extent_tail {int /*<<< orphan*/  et_checksum; } ;
struct ext4_extent_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_ext_block_csum (struct inode*,struct ext4_extent_header*) ; 
 struct ext4_extent_tail* find_ext4_extent_tail (struct ext4_extent_header*) ; 

__attribute__((used)) static void ext4_extent_block_csum_set(struct inode *inode,
		struct ext4_extent_header *eh)
{
	struct ext4_extent_tail *tail;

	tail = find_ext4_extent_tail(eh);
	tail->et_checksum = ext4_ext_block_csum(
			inode, eh);
}