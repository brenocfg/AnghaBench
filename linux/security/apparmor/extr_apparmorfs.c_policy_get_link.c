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
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct aa_ns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct aa_ns* aa_get_current_ns () ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  aafs_mnt ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_jump_link (struct path*) ; 
 int /*<<< orphan*/  ns_dir (struct aa_ns*) ; 

__attribute__((used)) static const char *policy_get_link(struct dentry *dentry,
				   struct inode *inode,
				   struct delayed_call *done)
{
	struct aa_ns *ns;
	struct path path;

	if (!dentry)
		return ERR_PTR(-ECHILD);
	ns = aa_get_current_ns();
	path.mnt = mntget(aafs_mnt);
	path.dentry = dget(ns_dir(ns));
	nd_jump_link(&path);
	aa_put_ns(ns);

	return NULL;
}