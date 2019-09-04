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
struct path {int /*<<< orphan*/  dentry; } ;
struct nameidata {int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int path_lookupat (struct nameidata*,unsigned int,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int vfs_open (struct path*,struct file*) ; 

__attribute__((used)) static int do_o_path(struct nameidata *nd, unsigned flags, struct file *file)
{
	struct path path;
	int error = path_lookupat(nd, flags, &path);
	if (!error) {
		audit_inode(nd->name, path.dentry, 0);
		error = vfs_open(&path, file);
		path_put(&path);
	}
	return error;
}