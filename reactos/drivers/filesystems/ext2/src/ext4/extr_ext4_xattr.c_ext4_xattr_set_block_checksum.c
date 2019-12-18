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
struct ext4_xattr_header {scalar_t__ h_checksum; } ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  int /*<<< orphan*/  PEXT2_MCB ;

/* Variables and functions */

__attribute__((used)) static void
ext4_xattr_set_block_checksum(PEXT2_MCB inode_ref,
			      ext4_fsblk_t blocknr,
			      struct ext4_xattr_header *header)
{
	/* TODO: Need METADATA_CSUM supports. */
	header->h_checksum = 0;
}