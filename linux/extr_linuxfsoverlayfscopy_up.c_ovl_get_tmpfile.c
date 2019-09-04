#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; int /*<<< orphan*/  rdev; } ;
struct ovl_copy_up_ctx {int /*<<< orphan*/  workdir; TYPE_1__ stat; scalar_t__ tmpfile; int /*<<< orphan*/  dentry; int /*<<< orphan*/  link; } ;
struct ovl_cattr {int mode; int /*<<< orphan*/  link; int /*<<< orphan*/  rdev; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int S_IFMT ; 
 struct cred* override_creds (struct cred*) ; 
 struct dentry* ovl_create_temp (int /*<<< orphan*/ ,struct ovl_cattr*) ; 
 struct dentry* ovl_do_tmpfile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int security_inode_copy_up (int /*<<< orphan*/ ,struct cred**) ; 

__attribute__((used)) static struct dentry *ovl_get_tmpfile(struct ovl_copy_up_ctx *c)
{
	int err;
	struct dentry *temp;
	const struct cred *old_creds = NULL;
	struct cred *new_creds = NULL;
	struct ovl_cattr cattr = {
		/* Can't properly set mode on creation because of the umask */
		.mode = c->stat.mode & S_IFMT,
		.rdev = c->stat.rdev,
		.link = c->link
	};

	err = security_inode_copy_up(c->dentry, &new_creds);
	temp = ERR_PTR(err);
	if (err < 0)
		goto out;

	if (new_creds)
		old_creds = override_creds(new_creds);

	if (c->tmpfile)
		temp = ovl_do_tmpfile(c->workdir, c->stat.mode);
	else
		temp = ovl_create_temp(c->workdir, &cattr);
out:
	if (new_creds) {
		revert_creds(old_creds);
		put_cred(new_creds);
	}

	return temp;
}