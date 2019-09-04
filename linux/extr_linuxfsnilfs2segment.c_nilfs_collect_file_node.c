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
struct nilfs_sc_info {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_bmap; } ;

/* Variables and functions */
 TYPE_1__* NILFS_I (struct inode*) ; 
 int nilfs_bmap_propagate (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static int nilfs_collect_file_node(struct nilfs_sc_info *sci,
				   struct buffer_head *bh,
				   struct inode *inode)
{
	return nilfs_bmap_propagate(NILFS_I(inode)->i_bmap, bh);
}