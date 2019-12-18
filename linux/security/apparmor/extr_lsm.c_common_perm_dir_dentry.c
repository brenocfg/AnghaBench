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
struct path_cond {int dummy; } ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int common_perm (char const*,struct path*,int /*<<< orphan*/ ,struct path_cond*) ; 

__attribute__((used)) static int common_perm_dir_dentry(const char *op, const struct path *dir,
				  struct dentry *dentry, u32 mask,
				  struct path_cond *cond)
{
	struct path path = { .mnt = dir->mnt, .dentry = dentry };

	return common_perm(op, &path, mask, cond);
}