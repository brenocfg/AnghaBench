#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ovl_fs {int noxattr; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct ovl_fs* s_fs_info; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ovl_do_setxattr (struct dentry*,char const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 

int ovl_check_setxattr(struct dentry *dentry, struct dentry *upperdentry,
		       const char *name, const void *value, size_t size,
		       int xerr)
{
	int err;
	struct ovl_fs *ofs = dentry->d_sb->s_fs_info;

	if (ofs->noxattr)
		return xerr;

	err = ovl_do_setxattr(upperdentry, name, value, size, 0);

	if (err == -EOPNOTSUPP) {
		pr_warn("overlayfs: cannot set %s xattr on upper\n", name);
		ofs->noxattr = true;
		return xerr;
	}

	return err;
}