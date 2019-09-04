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
struct inode {int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_writecount; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FL_LAYOUT ; 
 long const F_RDLCK ; 
 long const F_WRLCK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int d_count (struct dentry const*) ; 

__attribute__((used)) static int
check_conflicting_open(const struct dentry *dentry, const long arg, int flags)
{
	int ret = 0;
	struct inode *inode = dentry->d_inode;

	if (flags & FL_LAYOUT)
		return 0;

	if ((arg == F_RDLCK) && (atomic_read(&inode->i_writecount) > 0))
		return -EAGAIN;

	if ((arg == F_WRLCK) && ((d_count(dentry) > 1) ||
	    (atomic_read(&inode->i_count) > 1)))
		ret = -EAGAIN;

	return ret;
}