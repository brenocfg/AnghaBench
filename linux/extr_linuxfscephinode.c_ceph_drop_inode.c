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

int ceph_drop_inode(struct inode *inode)
{
	/*
	 * Positve dentry and corresponding inode are always accompanied
	 * in MDS reply. So no need to keep inode in the cache after
	 * dropping all its aliases.
	 */
	return 1;
}