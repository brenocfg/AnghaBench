#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ovl_readdir_data {struct ovl_cache_entry* first_maybe_whiteout; TYPE_1__* dentry; } ;
struct ovl_cache_entry {int /*<<< orphan*/  is_whiteout; int /*<<< orphan*/  len; int /*<<< orphan*/  name; struct ovl_cache_entry* next_maybe_whiteout; } ;
struct dentry {TYPE_2__* d_inode; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_rwsem; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int down_write_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_is_whiteout (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

__attribute__((used)) static int ovl_check_whiteouts(struct dentry *dir, struct ovl_readdir_data *rdd)
{
	int err;
	struct ovl_cache_entry *p;
	struct dentry *dentry;
	const struct cred *old_cred;

	old_cred = ovl_override_creds(rdd->dentry->d_sb);

	err = down_write_killable(&dir->d_inode->i_rwsem);
	if (!err) {
		while (rdd->first_maybe_whiteout) {
			p = rdd->first_maybe_whiteout;
			rdd->first_maybe_whiteout = p->next_maybe_whiteout;
			dentry = lookup_one_len(p->name, dir, p->len);
			if (!IS_ERR(dentry)) {
				p->is_whiteout = ovl_is_whiteout(dentry);
				dput(dentry);
			}
		}
		inode_unlock(dir->d_inode);
	}
	revert_creds(old_cred);

	return err;
}