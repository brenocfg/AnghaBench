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
struct inode {TYPE_1__* i_sb; } ;
typedef  int sector_t ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 scalar_t__ KEY_FORMAT_3_5 ; 
 scalar_t__ get_inode_item_key_version (struct inode*) ; 

__attribute__((used)) static int file_capable(struct inode *inode, sector_t block)
{
	/* it is new file. */
	if (get_inode_item_key_version(inode) != KEY_FORMAT_3_5 ||
	    /* old file, but 'block' is inside of 2gb */
	    block < (1 << (31 - inode->i_sb->s_blocksize_bits)))
		return 1;

	return 0;
}