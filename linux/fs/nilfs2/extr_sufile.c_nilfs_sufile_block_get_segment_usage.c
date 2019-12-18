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
typedef  void nilfs_segment_usage ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int mi_entry_size; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 
 int bh_offset (struct buffer_head*) ; 
 int nilfs_sufile_get_offset (struct inode const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nilfs_segment_usage *
nilfs_sufile_block_get_segment_usage(const struct inode *sufile, __u64 segnum,
				     struct buffer_head *bh, void *kaddr)
{
	return kaddr + bh_offset(bh) +
		nilfs_sufile_get_offset(sufile, segnum) *
		NILFS_MDT(sufile)->mi_entry_size;
}