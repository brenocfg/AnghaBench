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
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_TYPE_RENAME ; 
 int tomoyo_path2_perm (int /*<<< orphan*/ ,struct path*,struct path*) ; 

__attribute__((used)) static int tomoyo_path_rename(const struct path *old_parent,
			      struct dentry *old_dentry,
			      const struct path *new_parent,
			      struct dentry *new_dentry)
{
	struct path path1 = { .mnt = old_parent->mnt, .dentry = old_dentry };
	struct path path2 = { .mnt = new_parent->mnt, .dentry = new_dentry };

	return tomoyo_path2_perm(TOMOYO_TYPE_RENAME, &path1, &path2);
}