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
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  gfs2_aops ; 
 scalar_t__ gfs2_is_jdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_jdata_aops ; 

void gfs2_set_aops(struct inode *inode)
{
	if (gfs2_is_jdata(GFS2_I(inode)))
		inode->i_mapping->a_ops = &gfs2_jdata_aops;
	else
		inode->i_mapping->a_ops = &gfs2_aops;
}