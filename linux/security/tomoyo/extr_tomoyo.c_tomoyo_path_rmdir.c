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
 int /*<<< orphan*/  TOMOYO_TYPE_RMDIR ; 
 int tomoyo_path_perm (int /*<<< orphan*/ ,struct path*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tomoyo_path_rmdir(const struct path *parent, struct dentry *dentry)
{
	struct path path = { .mnt = parent->mnt, .dentry = dentry };

	return tomoyo_path_perm(TOMOYO_TYPE_RMDIR, &path, NULL);
}