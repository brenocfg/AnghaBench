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
 scalar_t__ NFS_STALE (struct inode*) ; 
 scalar_t__ generic_drop_inode (struct inode*) ; 

int nfs_drop_inode(struct inode *inode)
{
	return NFS_STALE(inode) || generic_drop_inode(inode);
}