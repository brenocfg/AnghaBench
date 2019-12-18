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
struct nameidata {int flags; struct path path; } ;

/* Variables and functions */
 int ENOTDIR ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 int LOOKUP_DIRECTORY ; 
 unsigned int LOOKUP_DOWN ; 
 int complete_walk (struct nameidata*) ; 
 int /*<<< orphan*/  d_can_lookup (int /*<<< orphan*/ *) ; 
 int handle_lookup_down (struct nameidata*) ; 
 int link_path_walk (char const*,struct nameidata*) ; 
 int lookup_last (struct nameidata*) ; 
 char* path_init (struct nameidata*,unsigned int) ; 
 int /*<<< orphan*/  terminate_walk (struct nameidata*) ; 
 char* trailing_symlink (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int path_lookupat(struct nameidata *nd, unsigned flags, struct path *path)
{
	const char *s = path_init(nd, flags);
	int err;

	if (unlikely(flags & LOOKUP_DOWN) && !IS_ERR(s)) {
		err = handle_lookup_down(nd);
		if (unlikely(err < 0))
			s = ERR_PTR(err);
	}

	while (!(err = link_path_walk(s, nd))
		&& ((err = lookup_last(nd)) > 0)) {
		s = trailing_symlink(nd);
	}
	if (!err)
		err = complete_walk(nd);

	if (!err && nd->flags & LOOKUP_DIRECTORY)
		if (!d_can_lookup(nd->path.dentry))
			err = -ENOTDIR;
	if (!err) {
		*path = nd->path;
		nd->path.mnt = NULL;
		nd->path.dentry = NULL;
	}
	terminate_walk(nd);
	return err;
}