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
typedef  int /*<<< orphan*/  umode_t ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,int /*<<< orphan*/ ,int) ; 
 struct dentry* vfs_tmpfile (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dentry *ovl_do_tmpfile(struct dentry *dentry, umode_t mode)
{
	struct dentry *ret = vfs_tmpfile(dentry, mode, 0);
	int err = PTR_ERR_OR_ZERO(ret);

	pr_debug("tmpfile(%pd2, 0%o) = %i\n", dentry, mode, err);
	return ret;
}