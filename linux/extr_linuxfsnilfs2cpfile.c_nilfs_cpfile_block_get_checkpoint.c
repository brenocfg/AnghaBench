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
typedef  void nilfs_checkpoint ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int mi_entry_size; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 
 int bh_offset (struct buffer_head*) ; 
 int nilfs_cpfile_get_offset (struct inode const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nilfs_checkpoint *
nilfs_cpfile_block_get_checkpoint(const struct inode *cpfile, __u64 cno,
				  struct buffer_head *bh,
				  void *kaddr)
{
	return kaddr + bh_offset(bh) + nilfs_cpfile_get_offset(cpfile, cno) *
		NILFS_MDT(cpfile)->mi_entry_size;
}