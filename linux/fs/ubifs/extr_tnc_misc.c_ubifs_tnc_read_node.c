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
struct ubifs_zbranch {int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; int /*<<< orphan*/  hash; int /*<<< orphan*/  len; union ubifs_key key; } ;
struct ubifs_wbuf {int dummy; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int UBIFS_KEY_OFFSET ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key*,char*) ; 
 int /*<<< orphan*/  key_read (struct ubifs_info*,void*,union ubifs_key*) ; 
 int key_type (struct ubifs_info*,union ubifs_key*) ; 
 int /*<<< orphan*/  keys_eq (struct ubifs_info*,union ubifs_key*,union ubifs_key*) ; 
 int /*<<< orphan*/  ubifs_bad_hash (struct ubifs_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ubifs_wbuf* ubifs_get_wbuf (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_node_check_hash (struct ubifs_info*,void*,int /*<<< orphan*/ ) ; 
 int ubifs_read_node (struct ubifs_info*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_read_node_wbuf (struct ubifs_wbuf*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ubifs_tnc_read_node(struct ubifs_info *c, struct ubifs_zbranch *zbr,
			void *node)
{
	union ubifs_key key1, *key = &zbr->key;
	int err, type = key_type(c, key);
	struct ubifs_wbuf *wbuf;

	/*
	 * 'zbr' has to point to on-flash node. The node may sit in a bud and
	 * may even be in a write buffer, so we have to take care about this.
	 */
	wbuf = ubifs_get_wbuf(c, zbr->lnum);
	if (wbuf)
		err = ubifs_read_node_wbuf(wbuf, node, type, zbr->len,
					   zbr->lnum, zbr->offs);
	else
		err = ubifs_read_node(c, node, type, zbr->len, zbr->lnum,
				      zbr->offs);

	if (err) {
		dbg_tnck(key, "key ");
		return err;
	}

	/* Make sure the key of the read node is correct */
	key_read(c, node + UBIFS_KEY_OFFSET, &key1);
	if (!keys_eq(c, key, &key1)) {
		ubifs_err(c, "bad key in node at LEB %d:%d",
			  zbr->lnum, zbr->offs);
		dbg_tnck(key, "looked for key ");
		dbg_tnck(&key1, "but found node's key ");
		ubifs_dump_node(c, node);
		return -EINVAL;
	}

	err = ubifs_node_check_hash(c, node, zbr->hash);
	if (err) {
		ubifs_bad_hash(c, node, zbr->hash, zbr->lnum, zbr->offs);
		return err;
	}

	return 0;
}