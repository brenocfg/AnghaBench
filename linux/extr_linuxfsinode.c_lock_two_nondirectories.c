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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_NONDIR2 ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (struct inode*,struct inode*) ; 

void lock_two_nondirectories(struct inode *inode1, struct inode *inode2)
{
	if (inode1 > inode2)
		swap(inode1, inode2);

	if (inode1 && !S_ISDIR(inode1->i_mode))
		inode_lock(inode1);
	if (inode2 && !S_ISDIR(inode2->i_mode) && inode2 != inode1)
		inode_lock_nested(inode2, I_MUTEX_NONDIR2);
}