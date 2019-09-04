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
 int complete_walk (struct nameidata*) ; 
 int link_path_walk (char const*,struct nameidata*) ; 
 char* path_init (struct nameidata*,unsigned int) ; 
 int /*<<< orphan*/  terminate_walk (struct nameidata*) ; 

__attribute__((used)) static int path_parentat(struct nameidata *nd, unsigned flags,
				struct path *parent)
{
	const char *s = path_init(nd, flags);
	int err = link_path_walk(s, nd);
	if (!err)
		err = complete_walk(nd);
	if (!err) {
		*parent = nd->path;
		nd->path.mnt = NULL;
		nd->path.dentry = NULL;
	}
	terminate_walk(nd);
	return err;
}