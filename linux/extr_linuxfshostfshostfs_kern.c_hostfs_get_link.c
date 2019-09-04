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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int ECHILD ; 
 int ENOMEM ; 
 char const* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  __putname (char*) ; 
 char* dentry_name (struct dentry*) ; 
 int hostfs_do_readlink (char*,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kfree_link ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *hostfs_get_link(struct dentry *dentry,
				   struct inode *inode,
				   struct delayed_call *done)
{
	char *link;
	if (!dentry)
		return ERR_PTR(-ECHILD);
	link = kmalloc(PATH_MAX, GFP_KERNEL);
	if (link) {
		char *path = dentry_name(dentry);
		int err = -ENOMEM;
		if (path) {
			err = hostfs_do_readlink(path, link, PATH_MAX);
			if (err == PATH_MAX)
				err = -E2BIG;
			__putname(path);
		}
		if (err < 0) {
			kfree(link);
			return ERR_PTR(err);
		}
	} else {
		return ERR_PTR(-ENOMEM);
	}

	set_delayed_call(done, kfree_link, link);
	return link;
}