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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,char const*,int /*<<< orphan*/ ,void const*,size_t,int,int) ; 
 int vfs_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 

__attribute__((used)) static inline int ovl_do_setxattr(struct dentry *dentry, const char *name,
				  const void *value, size_t size, int flags)
{
	int err = vfs_setxattr(dentry, name, value, size, flags);
	pr_debug("setxattr(%pd2, \"%s\", \"%*pE\", %zu, 0x%x) = %i\n",
		 dentry, name, min((int)size, 48), value, size, flags, err);
	return err;
}