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
struct ffs_epfile {int /*<<< orphan*/ * dentry; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  d_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ffs_epfile*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffs_epfiles_destroy(struct ffs_epfile *epfiles, unsigned count)
{
	struct ffs_epfile *epfile = epfiles;

	ENTER();

	for (; count; --count, ++epfile) {
		BUG_ON(mutex_is_locked(&epfile->mutex));
		if (epfile->dentry) {
			d_delete(epfile->dentry);
			dput(epfile->dentry);
			epfile->dentry = NULL;
		}
	}

	kfree(epfiles);
}