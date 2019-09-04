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
typedef  int /*<<< orphan*/  u32 ;
struct path {int dummy; } ;
struct kstat {int dummy; } ;

/* Variables and functions */
 int security_inode_getattr (struct path const*) ; 
 int vfs_getattr_nosec (struct path const*,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 

int vfs_getattr(const struct path *path, struct kstat *stat,
		u32 request_mask, unsigned int query_flags)
{
	int retval;

	retval = security_inode_getattr(path);
	if (retval)
		return retval;
	return vfs_getattr_nosec(path, stat, request_mask, query_flags);
}