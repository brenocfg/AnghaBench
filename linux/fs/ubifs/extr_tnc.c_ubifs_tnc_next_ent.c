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
struct ubifs_znode {struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {union ubifs_key key; int /*<<< orphan*/  len; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; scalar_t__ replaying; } ;
struct ubifs_dent_node {int dummy; } ;
struct fscrypt_name {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct ubifs_dent_node* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dbg_tnc (char*,int,struct ubifs_znode*,int) ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key*,char*) ; 
 int fallible_resolve_collision (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*,struct fscrypt_name const*,int /*<<< orphan*/ ) ; 
 scalar_t__ fname_len (struct fscrypt_name const*) ; 
 int /*<<< orphan*/  is_hash_key (struct ubifs_info*,union ubifs_key*) ; 
 scalar_t__ key_inum (struct ubifs_info*,union ubifs_key*) ; 
 int key_type (struct ubifs_info*,union ubifs_key*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int resolve_collision (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*,struct fscrypt_name const*) ; 
 int tnc_next (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 int tnc_read_hashed_node (struct ubifs_info*,struct ubifs_zbranch*,struct ubifs_dent_node*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*) ; 
 scalar_t__ unlikely (int) ; 

struct ubifs_dent_node *ubifs_tnc_next_ent(struct ubifs_info *c,
					   union ubifs_key *key,
					   const struct fscrypt_name *nm)
{
	int n, err, type = key_type(c, key);
	struct ubifs_znode *znode;
	struct ubifs_dent_node *dent;
	struct ubifs_zbranch *zbr;
	union ubifs_key *dkey;

	dbg_tnck(key, "key ");
	ubifs_assert(c, is_hash_key(c, key));

	mutex_lock(&c->tnc_mutex);
	err = ubifs_lookup_level0(c, key, &znode, &n);
	if (unlikely(err < 0))
		goto out_unlock;

	if (fname_len(nm) > 0) {
		if (err) {
			/* Handle collisions */
			if (c->replaying)
				err = fallible_resolve_collision(c, key, &znode, &n,
							 nm, 0);
			else
				err = resolve_collision(c, key, &znode, &n, nm);
			dbg_tnc("rc returned %d, znode %p, n %d",
				err, znode, n);
			if (unlikely(err < 0))
				goto out_unlock;
		}

		/* Now find next entry */
		err = tnc_next(c, &znode, &n);
		if (unlikely(err))
			goto out_unlock;
	} else {
		/*
		 * The full name of the entry was not given, in which case the
		 * behavior of this function is a little different and it
		 * returns current entry, not the next one.
		 */
		if (!err) {
			/*
			 * However, the given key does not exist in the TNC
			 * tree and @znode/@n variables contain the closest
			 * "preceding" element. Switch to the next one.
			 */
			err = tnc_next(c, &znode, &n);
			if (err)
				goto out_unlock;
		}
	}

	zbr = &znode->zbranch[n];
	dent = kmalloc(zbr->len, GFP_NOFS);
	if (unlikely(!dent)) {
		err = -ENOMEM;
		goto out_unlock;
	}

	/*
	 * The above 'tnc_next()' call could lead us to the next inode, check
	 * this.
	 */
	dkey = &zbr->key;
	if (key_inum(c, dkey) != key_inum(c, key) ||
	    key_type(c, dkey) != type) {
		err = -ENOENT;
		goto out_free;
	}

	err = tnc_read_hashed_node(c, zbr, dent);
	if (unlikely(err))
		goto out_free;

	mutex_unlock(&c->tnc_mutex);
	return dent;

out_free:
	kfree(dent);
out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return ERR_PTR(err);
}