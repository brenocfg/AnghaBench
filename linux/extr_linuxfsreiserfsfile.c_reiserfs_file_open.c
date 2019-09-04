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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tailpack; int /*<<< orphan*/  openers; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int dquot_file_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reiserfs_file_open(struct inode *inode, struct file *file)
{
	int err = dquot_file_open(inode, file);

	/* somebody might be tailpacking on final close; wait for it */
        if (!atomic_inc_not_zero(&REISERFS_I(inode)->openers)) {
		mutex_lock(&REISERFS_I(inode)->tailpack);
		atomic_inc(&REISERFS_I(inode)->openers);
		mutex_unlock(&REISERFS_I(inode)->tailpack);
	}
	return err;
}