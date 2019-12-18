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
typedef  int /*<<< orphan*/  val ;
struct inode {int dummy; } ;
typedef  unsigned long __u64 ;

/* Variables and functions */
 int ENODATA ; 
 int orangefs_inode_getxattr (struct inode*,char*,unsigned long*,int) ; 

__attribute__((used)) static int orangefs_getflags(struct inode *inode, unsigned long *uval)
{
	__u64 val = 0;
	int ret;

	ret = orangefs_inode_getxattr(inode,
				      "user.pvfs2.meta_hint",
				      &val, sizeof(val));
	if (ret < 0 && ret != -ENODATA)
		return ret;
	else if (ret == -ENODATA)
		val = 0;
	*uval = val;
	return 0;
}