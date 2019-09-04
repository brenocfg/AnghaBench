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
struct ubifs_zbranch {int lnum; int offs; } ;
struct ubifs_info {int gc_seq; int /*<<< orphan*/  tnc_mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 int fallible_read_node (struct ubifs_info*,union ubifs_key const*,struct ubifs_zbranch*,void*) ; 
 scalar_t__ is_hash_key (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ maybe_leb_gced (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tnc_read_hashed_node (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 
 scalar_t__ ubifs_get_wbuf (struct ubifs_info*,int) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*) ; 
 int ubifs_tnc_read_node (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 

int ubifs_tnc_locate(struct ubifs_info *c, const union ubifs_key *key,
		     void *node, int *lnum, int *offs)
{
	int found, n, err, safely = 0, gc_seq1;
	struct ubifs_znode *znode;
	struct ubifs_zbranch zbr, *zt;

again:
	mutex_lock(&c->tnc_mutex);
	found = ubifs_lookup_level0(c, key, &znode, &n);
	if (!found) {
		err = -ENOENT;
		goto out;
	} else if (found < 0) {
		err = found;
		goto out;
	}
	zt = &znode->zbranch[n];
	if (lnum) {
		*lnum = zt->lnum;
		*offs = zt->offs;
	}
	if (is_hash_key(c, key)) {
		/*
		 * In this case the leaf node cache gets used, so we pass the
		 * address of the zbranch and keep the mutex locked
		 */
		err = tnc_read_hashed_node(c, zt, node);
		goto out;
	}
	if (safely) {
		err = ubifs_tnc_read_node(c, zt, node);
		goto out;
	}
	/* Drop the TNC mutex prematurely and race with garbage collection */
	zbr = znode->zbranch[n];
	gc_seq1 = c->gc_seq;
	mutex_unlock(&c->tnc_mutex);

	if (ubifs_get_wbuf(c, zbr.lnum)) {
		/* We do not GC journal heads */
		err = ubifs_tnc_read_node(c, &zbr, node);
		return err;
	}

	err = fallible_read_node(c, key, &zbr, node);
	if (err <= 0 || maybe_leb_gced(c, zbr.lnum, gc_seq1)) {
		/*
		 * The node may have been GC'ed out from under us so try again
		 * while keeping the TNC mutex locked.
		 */
		safely = 1;
		goto again;
	}
	return 0;

out:
	mutex_unlock(&c->tnc_mutex);
	return err;
}