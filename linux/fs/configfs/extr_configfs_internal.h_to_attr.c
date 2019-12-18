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
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {scalar_t__ s_element; } ;
struct configfs_attribute {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct configfs_attribute * to_attr(struct dentry * dentry)
{
	struct configfs_dirent * sd = dentry->d_fsdata;
	return ((struct configfs_attribute *) sd->s_element);
}