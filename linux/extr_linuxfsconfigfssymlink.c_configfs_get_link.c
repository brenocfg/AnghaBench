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
 int ECHILD ; 
 int ENOMEM ; 
 char const* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int configfs_getlink (struct dentry*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kfree_link ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *configfs_get_link(struct dentry *dentry,
				     struct inode *inode,
				     struct delayed_call *done)
{
	char *body;
	int error;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	body = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!body)
		return ERR_PTR(-ENOMEM);

	error = configfs_getlink(dentry, body);
	if (!error) {
		set_delayed_call(done, kfree_link, body);
		return body;
	}

	kfree(body);
	return ERR_PTR(error);
}