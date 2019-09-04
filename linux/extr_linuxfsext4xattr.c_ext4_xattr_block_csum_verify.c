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
struct ext4_xattr_header {scalar_t__ h_checksum; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 struct ext4_xattr_header* BHDR (struct buffer_head*) ; 
 scalar_t__ ext4_has_metadata_csum (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_xattr_block_csum (struct inode*,int /*<<< orphan*/ ,struct ext4_xattr_header*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext4_xattr_block_csum_verify(struct inode *inode,
					struct buffer_head *bh)
{
	struct ext4_xattr_header *hdr = BHDR(bh);
	int ret = 1;

	if (ext4_has_metadata_csum(inode->i_sb)) {
		lock_buffer(bh);
		ret = (hdr->h_checksum == ext4_xattr_block_csum(inode,
							bh->b_blocknr, hdr));
		unlock_buffer(bh);
	}
	return ret;
}