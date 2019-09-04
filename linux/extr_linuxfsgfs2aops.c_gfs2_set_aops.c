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
struct inode {TYPE_1__* i_mapping; } ;
struct gfs2_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_ordered (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_writeback (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_jdata_aops ; 
 int /*<<< orphan*/  gfs2_ordered_aops ; 
 int /*<<< orphan*/  gfs2_writeback_aops ; 

void gfs2_set_aops(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);

	if (gfs2_is_writeback(ip))
		inode->i_mapping->a_ops = &gfs2_writeback_aops;
	else if (gfs2_is_ordered(ip))
		inode->i_mapping->a_ops = &gfs2_ordered_aops;
	else if (gfs2_is_jdata(ip))
		inode->i_mapping->a_ops = &gfs2_jdata_aops;
	else
		BUG();
}