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
typedef  void* time64_t ;
struct ubifs_znode {int /*<<< orphan*/  level; scalar_t__ cnext; struct ubifs_zbranch* zbranch; void* time; } ;
struct ubifs_zbranch {int /*<<< orphan*/  key; struct ubifs_znode* znode; } ;
struct ubifs_info {struct ubifs_zbranch zroot; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int /*<<< orphan*/  dbg_tnc (char*,int,...) ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key const*,char*) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 struct ubifs_znode* dirty_cow_znode (struct ubifs_info*,struct ubifs_zbranch*) ; 
 int /*<<< orphan*/  is_hash_key (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ keys_cmp (struct ubifs_info*,union ubifs_key const*,int /*<<< orphan*/ *) ; 
 void* ktime_get_seconds () ; 
 int tnc_prev (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 struct ubifs_znode* ubifs_load_znode (struct ubifs_info*,struct ubifs_zbranch*,struct ubifs_znode*,int) ; 
 int ubifs_search_zbranch (struct ubifs_info*,struct ubifs_znode*,union ubifs_key const*,int*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lookup_level0_dirty(struct ubifs_info *c, const union ubifs_key *key,
			       struct ubifs_znode **zn, int *n)
{
	int err, exact;
	struct ubifs_znode *znode;
	time64_t time = ktime_get_seconds();

	dbg_tnck(key, "search and dirty key ");

	znode = c->zroot.znode;
	if (unlikely(!znode)) {
		znode = ubifs_load_znode(c, &c->zroot, NULL, 0);
		if (IS_ERR(znode))
			return PTR_ERR(znode);
	}

	znode = dirty_cow_znode(c, &c->zroot);
	if (IS_ERR(znode))
		return PTR_ERR(znode);

	znode->time = time;

	while (1) {
		struct ubifs_zbranch *zbr;

		exact = ubifs_search_zbranch(c, znode, key, n);

		if (znode->level == 0)
			break;

		if (*n < 0)
			*n = 0;
		zbr = &znode->zbranch[*n];

		if (zbr->znode) {
			znode->time = time;
			znode = dirty_cow_znode(c, zbr);
			if (IS_ERR(znode))
				return PTR_ERR(znode);
			continue;
		}

		/* znode is not in TNC cache, load it from the media */
		znode = ubifs_load_znode(c, zbr, znode, *n);
		if (IS_ERR(znode))
			return PTR_ERR(znode);
		znode = dirty_cow_znode(c, zbr);
		if (IS_ERR(znode))
			return PTR_ERR(znode);
	}

	*zn = znode;
	if (exact || !is_hash_key(c, key) || *n != -1) {
		dbg_tnc("found %d, lvl %d, n %d", exact, znode->level, *n);
		return exact;
	}

	/*
	 * See huge comment at 'lookup_level0_dirty()' what is the rest of the
	 * code.
	 */
	err = tnc_prev(c, &znode, n);
	if (err == -ENOENT) {
		*n = -1;
		dbg_tnc("found 0, lvl %d, n -1", znode->level);
		return 0;
	}
	if (unlikely(err < 0))
		return err;
	if (keys_cmp(c, key, &znode->zbranch[*n].key)) {
		*n = -1;
		dbg_tnc("found 0, lvl %d, n -1", znode->level);
		return 0;
	}

	if (znode->cnext || !ubifs_zn_dirty(znode)) {
		znode = dirty_cow_bottom_up(c, znode);
		if (IS_ERR(znode))
			return PTR_ERR(znode);
	}

	dbg_tnc("found 1, lvl %d, n %d", znode->level, *n);
	*zn = znode;
	return 1;
}