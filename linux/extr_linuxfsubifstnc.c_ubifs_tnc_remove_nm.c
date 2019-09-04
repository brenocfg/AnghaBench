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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_znode {scalar_t__ cnext; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; scalar_t__ replaying; } ;
struct fscrypt_name {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int dbg_check_tnc (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_tnc (char*,int,struct ubifs_znode*,int) ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key const*,char*) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 int fallible_resolve_collision (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*,struct fscrypt_name const*,int /*<<< orphan*/ ) ; 
 int lookup_level0_dirty (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int resolve_collision (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*,struct fscrypt_name const*) ; 
 int tnc_delete (struct ubifs_info*,struct ubifs_znode*,int) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

int ubifs_tnc_remove_nm(struct ubifs_info *c, const union ubifs_key *key,
			const struct fscrypt_name *nm)
{
	int n, err;
	struct ubifs_znode *znode;

	mutex_lock(&c->tnc_mutex);
	dbg_tnck(key, "key ");
	err = lookup_level0_dirty(c, key, &znode, &n);
	if (err < 0)
		goto out_unlock;

	if (err) {
		if (c->replaying)
			err = fallible_resolve_collision(c, key, &znode, &n,
							 nm, 0);
		else
			err = resolve_collision(c, key, &znode, &n, nm);
		dbg_tnc("rc returned %d, znode %p, n %d", err, znode, n);
		if (err < 0)
			goto out_unlock;
		if (err) {
			/* Ensure the znode is dirtied */
			if (znode->cnext || !ubifs_zn_dirty(znode)) {
				znode = dirty_cow_bottom_up(c, znode);
				if (IS_ERR(znode)) {
					err = PTR_ERR(znode);
					goto out_unlock;
				}
			}
			err = tnc_delete(c, znode, n);
		}
	}

out_unlock:
	if (!err)
		err = dbg_check_tnc(c, 0);
	mutex_unlock(&c->tnc_mutex);
	return err;
}