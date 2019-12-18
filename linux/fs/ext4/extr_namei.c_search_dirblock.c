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
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int ext4_search_dir (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,struct ext4_filename*,unsigned int,struct ext4_dir_entry_2**) ; 

__attribute__((used)) static inline int search_dirblock(struct buffer_head *bh,
				  struct inode *dir,
				  struct ext4_filename *fname,
				  unsigned int offset,
				  struct ext4_dir_entry_2 **res_dir)
{
	return ext4_search_dir(bh, bh->b_data, dir->i_sb->s_blocksize, dir,
			       fname, offset, res_dir);
}