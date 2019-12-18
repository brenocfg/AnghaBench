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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int nfs_wb_all (struct inode*) ; 

int nfs_sync_inode(struct inode *inode)
{
	inode_dio_wait(inode);
	return nfs_wb_all(inode);
}