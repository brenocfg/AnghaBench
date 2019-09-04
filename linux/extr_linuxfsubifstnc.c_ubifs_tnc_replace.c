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
struct ubifs_znode {struct ubifs_zbranch* zbranch; scalar_t__ cnext; } ;
struct ubifs_zbranch {int lnum; int offs; int len; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int dbg_check_tnc (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_tnc (char*,int,struct ubifs_znode*,int,int,int) ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key const*,char*,int,int,int,int,int) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 scalar_t__ is_hash_key (struct ubifs_info*,union ubifs_key const*) ; 
 int /*<<< orphan*/  lnc_free (struct ubifs_zbranch*) ; 
 int lookup_level0_dirty (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int resolve_collision_directly (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*,int,int) ; 
 int ubifs_add_dirt (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

int ubifs_tnc_replace(struct ubifs_info *c, const union ubifs_key *key,
		      int old_lnum, int old_offs, int lnum, int offs, int len)
{
	int found, n, err = 0;
	struct ubifs_znode *znode;

	mutex_lock(&c->tnc_mutex);
	dbg_tnck(key, "old LEB %d:%d, new LEB %d:%d, len %d, key ", old_lnum,
		 old_offs, lnum, offs, len);
	found = lookup_level0_dirty(c, key, &znode, &n);
	if (found < 0) {
		err = found;
		goto out_unlock;
	}

	if (found == 1) {
		struct ubifs_zbranch *zbr = &znode->zbranch[n];

		found = 0;
		if (zbr->lnum == old_lnum && zbr->offs == old_offs) {
			lnc_free(zbr);
			err = ubifs_add_dirt(c, zbr->lnum, zbr->len);
			if (err)
				goto out_unlock;
			zbr->lnum = lnum;
			zbr->offs = offs;
			zbr->len = len;
			found = 1;
		} else if (is_hash_key(c, key)) {
			found = resolve_collision_directly(c, key, &znode, &n,
							   old_lnum, old_offs);
			dbg_tnc("rc returned %d, znode %p, n %d, LEB %d:%d",
				found, znode, n, old_lnum, old_offs);
			if (found < 0) {
				err = found;
				goto out_unlock;
			}

			if (found) {
				/* Ensure the znode is dirtied */
				if (znode->cnext || !ubifs_zn_dirty(znode)) {
					znode = dirty_cow_bottom_up(c, znode);
					if (IS_ERR(znode)) {
						err = PTR_ERR(znode);
						goto out_unlock;
					}
				}
				zbr = &znode->zbranch[n];
				lnc_free(zbr);
				err = ubifs_add_dirt(c, zbr->lnum,
						     zbr->len);
				if (err)
					goto out_unlock;
				zbr->lnum = lnum;
				zbr->offs = offs;
				zbr->len = len;
			}
		}
	}

	if (!found)
		err = ubifs_add_dirt(c, lnum, len);

	if (!err)
		err = dbg_check_tnc(c, 0);

out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return err;
}