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
 int /*<<< orphan*/  ecryptfs_inode_to_lower (struct inode*) ; 
 int inode_permission (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ecryptfs_permission(struct inode *inode, int mask)
{
	return inode_permission(ecryptfs_inode_to_lower(inode), mask);
}