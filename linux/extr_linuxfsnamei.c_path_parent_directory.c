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
struct path {struct dentry* dentry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  path_connected (struct path*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int path_parent_directory(struct path *path)
{
	struct dentry *old = path->dentry;
	/* rare case of legitimate dget_parent()... */
	path->dentry = dget_parent(path->dentry);
	dput(old);
	if (unlikely(!path_connected(path)))
		return -ENOENT;
	return 0;
}