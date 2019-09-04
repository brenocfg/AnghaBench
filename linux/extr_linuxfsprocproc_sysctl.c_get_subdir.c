#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctl_table_set {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nreg; struct ctl_table_set* set; } ;
struct ctl_dir {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 struct ctl_dir* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ctl_dir*) ; 
 int /*<<< orphan*/  PTR_ERR (struct ctl_dir*) ; 
 int /*<<< orphan*/  drop_sysctl_table (TYPE_1__*) ; 
 struct ctl_dir* find_subdir (struct ctl_dir*,char const*,int) ; 
 int insert_header (struct ctl_dir*,TYPE_1__*) ; 
 struct ctl_dir* new_dir (struct ctl_table_set*,char const*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 
 int /*<<< orphan*/  sysctl_print_dir (struct ctl_dir*) ; 

__attribute__((used)) static struct ctl_dir *get_subdir(struct ctl_dir *dir,
				  const char *name, int namelen)
{
	struct ctl_table_set *set = dir->header.set;
	struct ctl_dir *subdir, *new = NULL;
	int err;

	spin_lock(&sysctl_lock);
	subdir = find_subdir(dir, name, namelen);
	if (!IS_ERR(subdir))
		goto found;
	if (PTR_ERR(subdir) != -ENOENT)
		goto failed;

	spin_unlock(&sysctl_lock);
	new = new_dir(set, name, namelen);
	spin_lock(&sysctl_lock);
	subdir = ERR_PTR(-ENOMEM);
	if (!new)
		goto failed;

	/* Was the subdir added while we dropped the lock? */
	subdir = find_subdir(dir, name, namelen);
	if (!IS_ERR(subdir))
		goto found;
	if (PTR_ERR(subdir) != -ENOENT)
		goto failed;

	/* Nope.  Use the our freshly made directory entry. */
	err = insert_header(dir, &new->header);
	subdir = ERR_PTR(err);
	if (err)
		goto failed;
	subdir = new;
found:
	subdir->header.nreg++;
failed:
	if (IS_ERR(subdir)) {
		pr_err("sysctl could not get directory: ");
		sysctl_print_dir(dir);
		pr_cont("/%*.*s %ld\n",
			namelen, namelen, name, PTR_ERR(subdir));
	}
	drop_sysctl_table(&dir->header);
	if (new)
		drop_sysctl_table(&new->header);
	spin_unlock(&sysctl_lock);
	return subdir;
}