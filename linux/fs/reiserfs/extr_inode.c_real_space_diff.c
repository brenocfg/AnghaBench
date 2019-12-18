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
struct inode {int i_size; TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
typedef  int loff_t ;
struct TYPE_2__ {int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int UNFM_P_SIZE ; 

__attribute__((used)) static int real_space_diff(struct inode *inode, int sd_size)
{
	int bytes;
	loff_t blocksize = inode->i_sb->s_blocksize;

	if (S_ISLNK(inode->i_mode) || S_ISDIR(inode->i_mode))
		return sd_size;

	/*
	 * End of file is also in full block with indirect reference, so round
	 * up to the next block.
	 *
	 * there is just no way to know if the tail is actually packed
	 * on the file, so we have to assume it isn't.  When we pack the
	 * tail, we add 4 bytes to pretend there really is an unformatted
	 * node pointer
	 */
	bytes =
	    ((inode->i_size +
	      (blocksize - 1)) >> inode->i_sb->s_blocksize_bits) * UNFM_P_SIZE +
	    sd_size;
	return bytes;
}