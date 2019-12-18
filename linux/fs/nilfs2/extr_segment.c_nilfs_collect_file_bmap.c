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
struct nilfs_sc_info {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int nilfs_segctor_add_file_block (struct nilfs_sc_info*,struct buffer_head*,struct inode*,int) ; 

__attribute__((used)) static int nilfs_collect_file_bmap(struct nilfs_sc_info *sci,
				   struct buffer_head *bh,
				   struct inode *inode)
{
	WARN_ON(!buffer_dirty(bh));
	return nilfs_segctor_add_file_block(sci, bh, inode, sizeof(__le64));
}