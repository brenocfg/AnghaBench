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
struct dlmfs_inode_private {int /*<<< orphan*/  ip_vfs_inode; int /*<<< orphan*/ * ip_parent; int /*<<< orphan*/ * ip_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlmfs_init_once(void *foo)
{
	struct dlmfs_inode_private *ip =
		(struct dlmfs_inode_private *) foo;

	ip->ip_conn = NULL;
	ip->ip_parent = NULL;

	inode_init_once(&ip->ip_vfs_inode);
}