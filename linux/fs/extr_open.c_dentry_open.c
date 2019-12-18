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
struct path {int /*<<< orphan*/  mnt; } ;
struct file {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct file*) ; 
 struct file* alloc_empty_file (int,struct cred const*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  validate_creds (struct cred const*) ; 
 int vfs_open (struct path const*,struct file*) ; 

struct file *dentry_open(const struct path *path, int flags,
			 const struct cred *cred)
{
	int error;
	struct file *f;

	validate_creds(cred);

	/* We must always pass in a valid mount pointer. */
	BUG_ON(!path->mnt);

	f = alloc_empty_file(flags, cred);
	if (!IS_ERR(f)) {
		error = vfs_open(path, f);
		if (error) {
			fput(f);
			f = ERR_PTR(error);
		}
	}
	return f;
}