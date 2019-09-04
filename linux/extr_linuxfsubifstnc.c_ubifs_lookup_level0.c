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
struct ubifs_znode {int /*<<< orphan*/  level; struct ubifs_zbranch* zbranch; void* time; } ;
struct ubifs_zbranch {int /*<<< orphan*/  key; struct ubifs_znode* znode; } ;
struct ubifs_info {struct ubifs_zbranch zroot; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 scalar_t__ UBIFS_INVALID_KEY ; 
 int /*<<< orphan*/  dbg_tnc (char*,int,...) ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key const*,char*) ; 
 int /*<<< orphan*/  is_hash_key (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ key_type (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ keys_cmp (struct ubifs_info*,union ubifs_key const*,int /*<<< orphan*/ *) ; 
 void* ktime_get_seconds () ; 
 int tnc_prev (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct ubifs_znode* ubifs_load_znode (struct ubifs_info*,struct ubifs_zbranch*,struct ubifs_znode*,int) ; 
 int ubifs_search_zbranch (struct ubifs_info*,struct ubifs_znode*,union ubifs_key const*,int*) ; 
 scalar_t__ unlikely (int) ; 

int ubifs_lookup_level0(struct ubifs_info *c, const union ubifs_key *key,
			struct ubifs_znode **zn, int *n)
{
	int err, exact;
	struct ubifs_znode *znode;
	time64_t time = ktime_get_seconds();

	dbg_tnck(key, "search key ");
	ubifs_assert(c, key_type(c, key) < UBIFS_INVALID_KEY);

	znode = c->zroot.znode;
	if (unlikely(!znode)) {
		znode = ubifs_load_znode(c, &c->zroot, NULL, 0);
		if (IS_ERR(znode))
			return PTR_ERR(znode);
	}

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
			znode = zbr->znode;
			continue;
		}

		/* znode is not in TNC cache, load it from the media */
		znode = ubifs_load_znode(c, zbr, znode, *n);
		if (IS_ERR(znode))
			return PTR_ERR(znode);
	}

	*zn = znode;
	if (exact || !is_hash_key(c, key) || *n != -1) {
		dbg_tnc("found %d, lvl %d, n %d", exact, znode->level, *n);
		return exact;
	}

	/*
	 * Here is a tricky place. We have not found the key and this is a
	 * "hashed" key, which may collide. The rest of the code deals with
	 * situations like this:
	 *
	 *                  | 3 | 5 |
	 *                  /       \
	 *          | 3 | 5 |      | 6 | 7 | (x)
	 *
	 * Or more a complex example:
	 *
	 *                | 1 | 5 |
	 *                /       \
	 *       | 1 | 3 |         | 5 | 8 |
	 *              \           /
	 *          | 5 | 5 |   | 6 | 7 | (x)
	 *
	 * In the examples, if we are looking for key "5", we may reach nodes
	 * marked with "(x)". In this case what we have do is to look at the
	 * left and see if there is "5" key there. If there is, we have to
	 * return it.
	 *
	 * Note, this whole situation is possible because we allow to have
	 * elements which are equivalent to the next key in the parent in the
	 * children of current znode. For example, this happens if we split a
	 * znode like this: | 3 | 5 | 5 | 6 | 7 |, which results in something
	 * like this:
	 *                      | 3 | 5 |
	 *                       /     \
	 *                | 3 | 5 |   | 5 | 6 | 7 |
	 *                              ^
	 * And this becomes what is at the first "picture" after key "5" marked
	 * with "^" is removed. What could be done is we could prohibit
	 * splitting in the middle of the colliding sequence. Also, when
	 * removing the leftmost key, we would have to correct the key of the
	 * parent node, which would introduce additional complications. Namely,
	 * if we changed the leftmost key of the parent znode, the garbage
	 * collector would be unable to find it (GC is doing this when GC'ing
	 * indexing LEBs). Although we already have an additional RB-tree where
	 * we save such changed znodes (see 'ins_clr_old_idx_znode()') until
	 * after the commit. But anyway, this does not look easy to implement
	 * so we did not try this.
	 */
	err = tnc_prev(c, &znode, n);
	if (err == -ENOENT) {
		dbg_tnc("found 0, lvl %d, n -1", znode->level);
		*n = -1;
		return 0;
	}
	if (unlikely(err < 0))
		return err;
	if (keys_cmp(c, key, &znode->zbranch[*n].key)) {
		dbg_tnc("found 0, lvl %d, n -1", znode->level);
		*n = -1;
		return 0;
	}

	dbg_tnc("found 1, lvl %d, n %d", znode->level, *n);
	*zn = znode;
	return 1;
}