#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {scalar_t__ i_nlink; } ;

/* Variables and functions */
 TYPE_3__* OVL_I (TYPE_1__*) ; 
 int /*<<< orphan*/  OVL_INDEX ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_cleanup_index (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_test_flag (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

void ovl_nlink_end(struct dentry *dentry, bool locked)
{
	if (locked) {
		if (ovl_test_flag(OVL_INDEX, d_inode(dentry)) &&
		    d_inode(dentry)->i_nlink == 0) {
			const struct cred *old_cred;

			old_cred = ovl_override_creds(dentry->d_sb);
			ovl_cleanup_index(dentry);
			revert_creds(old_cred);
		}

		mutex_unlock(&OVL_I(d_inode(dentry))->lock);
	}
}