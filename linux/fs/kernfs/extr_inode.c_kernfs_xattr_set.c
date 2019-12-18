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
struct kernfs_node {int dummy; } ;
struct kernfs_iattrs {int /*<<< orphan*/  xattrs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kernfs_iattrs* kernfs_iattrs (struct kernfs_node*) ; 
 int simple_xattr_set (int /*<<< orphan*/ *,char const*,void const*,size_t,int) ; 

int kernfs_xattr_set(struct kernfs_node *kn, const char *name,
		     const void *value, size_t size, int flags)
{
	struct kernfs_iattrs *attrs = kernfs_iattrs(kn);
	if (!attrs)
		return -ENOMEM;

	return simple_xattr_set(&attrs->xattrs, name, value, size, flags);
}