#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
struct TYPE_3__ {int /*<<< orphan*/  h_checksum; } ;

/* Variables and functions */
 TYPE_1__* BHDR (struct buffer_head*) ; 
 scalar_t__ ext4_has_metadata_csum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_block_csum (struct inode*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void ext4_xattr_block_csum_set(struct inode *inode,
				      struct buffer_head *bh)
{
	if (ext4_has_metadata_csum(inode->i_sb))
		BHDR(bh)->h_checksum = ext4_xattr_block_csum(inode,
						bh->b_blocknr, BHDR(bh));
}