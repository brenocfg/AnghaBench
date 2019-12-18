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
struct ubifs_znode {int dummy; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;
struct ubifs_dent_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_hash_key (struct ubifs_info*,union ubifs_key const*) ; 
 int /*<<< orphan*/  key_inum (struct ubifs_info*,union ubifs_key const*) ; 
 int /*<<< orphan*/  lowest_dent_key (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int search_dh_cookie (struct ubifs_info*,union ubifs_key const*,struct ubifs_dent_node*,int /*<<< orphan*/ ,struct ubifs_znode**,int*,int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_lookup_dh(struct ubifs_info *c, const union ubifs_key *key,
			struct ubifs_dent_node *dent, uint32_t cookie)
{
	int n, err;
	struct ubifs_znode *znode;
	union ubifs_key start_key;

	ubifs_assert(c, is_hash_key(c, key));

	lowest_dent_key(c, &start_key, key_inum(c, key));

	mutex_lock(&c->tnc_mutex);
	err = ubifs_lookup_level0(c, &start_key, &znode, &n);
	if (unlikely(err < 0))
		goto out_unlock;

	err = search_dh_cookie(c, key, dent, cookie, &znode, &n, err);

out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return err;
}