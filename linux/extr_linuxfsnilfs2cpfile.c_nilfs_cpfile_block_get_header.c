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
typedef  void nilfs_cpfile_header ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int bh_offset (struct buffer_head*) ; 

__attribute__((used)) static inline struct nilfs_cpfile_header *
nilfs_cpfile_block_get_header(const struct inode *cpfile,
			      struct buffer_head *bh,
			      void *kaddr)
{
	return kaddr + bh_offset(bh);
}