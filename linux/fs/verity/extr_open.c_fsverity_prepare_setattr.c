#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iattr {int ia_valid; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int EPERM ; 
 scalar_t__ IS_VERITY (TYPE_1__*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int fsverity_prepare_setattr(struct dentry *dentry, struct iattr *attr)
{
	if (IS_VERITY(d_inode(dentry)) && (attr->ia_valid & ATTR_SIZE)) {
		pr_debug("Denying truncate of verity file (ino %lu)\n",
			 d_inode(dentry)->i_ino);
		return -EPERM;
	}
	return 0;
}