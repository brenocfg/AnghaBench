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
struct path {int /*<<< orphan*/ * dentry; int /*<<< orphan*/ * mnt; } ;
struct nameidata {struct path path; } ;

/* Variables and functions */
 int /*<<< orphan*/  follow_mount (struct path*) ; 
 int link_path_walk (char const*,struct nameidata*) ; 
 int mountpoint_last (struct nameidata*) ; 
 char* path_init (struct nameidata*,unsigned int) ; 
 int /*<<< orphan*/  terminate_walk (struct nameidata*) ; 
 char* trailing_symlink (struct nameidata*) ; 

__attribute__((used)) static int
path_mountpoint(struct nameidata *nd, unsigned flags, struct path *path)
{
	const char *s = path_init(nd, flags);
	int err;

	while (!(err = link_path_walk(s, nd)) &&
		(err = mountpoint_last(nd)) > 0) {
		s = trailing_symlink(nd);
	}
	if (!err) {
		*path = nd->path;
		nd->path.mnt = NULL;
		nd->path.dentry = NULL;
		follow_mount(path);
	}
	terminate_walk(nd);
	return err;
}