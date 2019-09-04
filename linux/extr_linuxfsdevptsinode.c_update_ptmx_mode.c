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
struct TYPE_2__ {int ptmxmode; } ;
struct pts_fs_info {TYPE_1__ mount_opts; scalar_t__ ptmx_dentry; } ;
struct inode {int i_mode; } ;

/* Variables and functions */
 int S_IFCHR ; 
 struct inode* d_inode (scalar_t__) ; 

__attribute__((used)) static void update_ptmx_mode(struct pts_fs_info *fsi)
{
	struct inode *inode;
	if (fsi->ptmx_dentry) {
		inode = d_inode(fsi->ptmx_dentry);
		inode->i_mode = S_IFCHR|fsi->mount_opts.ptmxmode;
	}
}