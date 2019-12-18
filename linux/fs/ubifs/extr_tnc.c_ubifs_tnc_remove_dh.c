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
typedef  int /*<<< orphan*/  uint32_t ;
struct ubifs_znode {scalar_t__ cnext; struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {int dummy; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/  double_hash; } ;
struct ubifs_dent_node {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int /*<<< orphan*/  UBIFS_MAX_DENT_NODE_SZ ; 
 int dbg_check_tnc (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  key_inum (struct ubifs_info*,union ubifs_key const*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lookup_level0_dirty (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  lowest_dent_key (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int search_dh_cookie (struct ubifs_info*,union ubifs_key const*,struct ubifs_dent_node*,int /*<<< orphan*/ ,struct ubifs_znode**,int*,int) ; 
 int tnc_delete (struct ubifs_info*,struct ubifs_znode*,int) ; 
 int tnc_read_hashed_node (struct ubifs_info*,struct ubifs_zbranch*,struct ubifs_dent_node*) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 
 scalar_t__ unlikely (int) ; 

int ubifs_tnc_remove_dh(struct ubifs_info *c, const union ubifs_key *key,
			uint32_t cookie)
{
	int n, err;
	struct ubifs_znode *znode;
	struct ubifs_dent_node *dent;
	struct ubifs_zbranch *zbr;

	if (!c->double_hash)
		return -EOPNOTSUPP;

	mutex_lock(&c->tnc_mutex);
	err = lookup_level0_dirty(c, key, &znode, &n);
	if (err <= 0)
		goto out_unlock;

	zbr = &znode->zbranch[n];
	dent = kmalloc(UBIFS_MAX_DENT_NODE_SZ, GFP_NOFS);
	if (!dent) {
		err = -ENOMEM;
		goto out_unlock;
	}

	err = tnc_read_hashed_node(c, zbr, dent);
	if (err)
		goto out_free;

	/* If the cookie does not match, we're facing a hash collision. */
	if (le32_to_cpu(dent->cookie) != cookie) {
		union ubifs_key start_key;

		lowest_dent_key(c, &start_key, key_inum(c, key));

		err = ubifs_lookup_level0(c, &start_key, &znode, &n);
		if (unlikely(err < 0))
			goto out_free;

		err = search_dh_cookie(c, key, dent, cookie, &znode, &n, err);
		if (err)
			goto out_free;
	}

	if (znode->cnext || !ubifs_zn_dirty(znode)) {
		znode = dirty_cow_bottom_up(c, znode);
		if (IS_ERR(znode)) {
			err = PTR_ERR(znode);
			goto out_free;
		}
	}
	err = tnc_delete(c, znode, n);

out_free:
	kfree(dent);
out_unlock:
	if (!err)
		err = dbg_check_tnc(c, 0);
	mutex_unlock(&c->tnc_mutex);
	return err;
}