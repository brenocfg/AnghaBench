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
struct dentry {int /*<<< orphan*/  d_fsdata; } ;
struct debugfs_fsdata {int /*<<< orphan*/  active_users_drained; int /*<<< orphan*/  active_users; } ;

/* Variables and functions */
 struct debugfs_fsdata* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void debugfs_file_put(struct dentry *dentry)
{
	struct debugfs_fsdata *fsd = READ_ONCE(dentry->d_fsdata);

	if (refcount_dec_and_test(&fsd->active_users))
		complete(&fsd->active_users_drained);
}