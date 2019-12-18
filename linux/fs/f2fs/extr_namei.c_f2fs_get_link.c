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
 int /*<<< orphan*/  ENOENT ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 int /*<<< orphan*/  clear_delayed_call (struct delayed_call*) ; 
 int /*<<< orphan*/  do_delayed_call (struct delayed_call*) ; 
 char* page_get_link (struct dentry*,struct inode*,struct delayed_call*) ; 

__attribute__((used)) static const char *f2fs_get_link(struct dentry *dentry,
				 struct inode *inode,
				 struct delayed_call *done)
{
	const char *link = page_get_link(dentry, inode, done);
	if (!IS_ERR(link) && !*link) {
		/* this is broken symlink case */
		do_delayed_call(done);
		clear_delayed_call(done);
		link = ERR_PTR(-ENOENT);
	}
	return link;
}