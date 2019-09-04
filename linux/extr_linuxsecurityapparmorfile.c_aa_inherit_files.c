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
struct files_struct {int dummy; } ;
struct file {int dummy; } ;
struct cred {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDWR ; 
 struct aa_label* aa_get_newest_cred_label (struct cred const*) ; 
 int /*<<< orphan*/  aa_null ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 struct file* dentry_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cred const*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 unsigned int iterate_fd (struct files_struct*,unsigned int,int /*<<< orphan*/ ,struct aa_label*) ; 
 int /*<<< orphan*/  match_file ; 
 int /*<<< orphan*/  replace_fd (unsigned int,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_tty (struct aa_label*) ; 

void aa_inherit_files(const struct cred *cred, struct files_struct *files)
{
	struct aa_label *label = aa_get_newest_cred_label(cred);
	struct file *devnull = NULL;
	unsigned int n;

	revalidate_tty(label);

	/* Revalidate access to inherited open files. */
	n = iterate_fd(files, 0, match_file, label);
	if (!n) /* none found? */
		goto out;

	devnull = dentry_open(&aa_null, O_RDWR, cred);
	if (IS_ERR(devnull))
		devnull = NULL;
	/* replace all the matching ones with this */
	do {
		replace_fd(n - 1, devnull, 0);
	} while ((n = iterate_fd(files, n, match_file, label)) != 0);
	if (devnull)
		fput(devnull);
out:
	aa_put_label(label);
}