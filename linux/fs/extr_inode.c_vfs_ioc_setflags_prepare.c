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
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 int EPERM ; 
 unsigned int FS_APPEND_FL ; 
 unsigned int FS_IMMUTABLE_FL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

int vfs_ioc_setflags_prepare(struct inode *inode, unsigned int oldflags,
			     unsigned int flags)
{
	/*
	 * The IMMUTABLE and APPEND_ONLY flags can only be changed by
	 * the relevant capability.
	 *
	 * This test looks nicer. Thanks to Pauline Middelink
	 */
	if ((flags ^ oldflags) & (FS_APPEND_FL | FS_IMMUTABLE_FL) &&
	    !capable(CAP_LINUX_IMMUTABLE))
		return -EPERM;

	return 0;
}