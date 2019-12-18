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
 int ENODATA ; 
 struct kernfs_iattrs* kernfs_iattrs_noalloc (struct kernfs_node*) ; 
 int simple_xattr_get (int /*<<< orphan*/ *,char const*,void*,size_t) ; 

int kernfs_xattr_get(struct kernfs_node *kn, const char *name,
		     void *value, size_t size)
{
	struct kernfs_iattrs *attrs = kernfs_iattrs_noalloc(kn);
	if (!attrs)
		return -ENODATA;

	return simple_xattr_get(&attrs->xattrs, name, value, size);
}