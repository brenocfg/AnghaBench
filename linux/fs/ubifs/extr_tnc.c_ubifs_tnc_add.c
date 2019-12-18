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
typedef  int /*<<< orphan*/  u8 ;
struct ubifs_znode {struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {int lnum; int offs; int len; int /*<<< orphan*/  hash; int /*<<< orphan*/  key; int /*<<< orphan*/ * znode; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;

/* Variables and functions */
 int dbg_check_tnc (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key const*,char*,int,int,int) ; 
 int /*<<< orphan*/  key_copy (struct ubifs_info*,union ubifs_key const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lnc_free (struct ubifs_zbranch*) ; 
 int lookup_level0_dirty (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tnc_insert (struct ubifs_info*,struct ubifs_znode*,struct ubifs_zbranch*,int) ; 
 int ubifs_add_dirt (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  ubifs_copy_hash (struct ubifs_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ubifs_tnc_add(struct ubifs_info *c, const union ubifs_key *key, int lnum,
		  int offs, int len, const u8 *hash)
{
	int found, n, err = 0;
	struct ubifs_znode *znode;

	mutex_lock(&c->tnc_mutex);
	dbg_tnck(key, "%d:%d, len %d, key ", lnum, offs, len);
	found = lookup_level0_dirty(c, key, &znode, &n);
	if (!found) {
		struct ubifs_zbranch zbr;

		zbr.znode = NULL;
		zbr.lnum = lnum;
		zbr.offs = offs;
		zbr.len = len;
		ubifs_copy_hash(c, hash, zbr.hash);
		key_copy(c, key, &zbr.key);
		err = tnc_insert(c, znode, &zbr, n + 1);
	} else if (found == 1) {
		struct ubifs_zbranch *zbr = &znode->zbranch[n];

		lnc_free(zbr);
		err = ubifs_add_dirt(c, zbr->lnum, zbr->len);
		zbr->lnum = lnum;
		zbr->offs = offs;
		zbr->len = len;
		ubifs_copy_hash(c, hash, zbr->hash);
	} else
		err = found;
	if (!err)
		err = dbg_check_tnc(c, 0);
	mutex_unlock(&c->tnc_mutex);

	return err;
}