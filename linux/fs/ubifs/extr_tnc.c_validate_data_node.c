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
struct ubifs_zbranch {int lnum; scalar_t__ offs; int len; union ubifs_key key; int /*<<< orphan*/  hash; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_ch {scalar_t__ node_type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UBIFS_DATA_NODE ; 
 int UBIFS_KEY_OFFSET ; 
 int /*<<< orphan*/  dbg_tnck (union ubifs_key*,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  key_read (struct ubifs_info*,void*,union ubifs_key*) ; 
 int /*<<< orphan*/  keys_eq (struct ubifs_info*,union ubifs_key*,union ubifs_key*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_bad_hash (struct ubifs_info*,void*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int ubifs_check_node (struct ubifs_info*,void*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,...) ; 
 int ubifs_node_check_hash (struct ubifs_info*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_data_node(struct ubifs_info *c, void *buf,
			      struct ubifs_zbranch *zbr)
{
	union ubifs_key key1;
	struct ubifs_ch *ch = buf;
	int err, len;

	if (ch->node_type != UBIFS_DATA_NODE) {
		ubifs_err(c, "bad node type (%d but expected %d)",
			  ch->node_type, UBIFS_DATA_NODE);
		goto out_err;
	}

	err = ubifs_check_node(c, buf, zbr->lnum, zbr->offs, 0, 0);
	if (err) {
		ubifs_err(c, "expected node type %d", UBIFS_DATA_NODE);
		goto out;
	}

	err = ubifs_node_check_hash(c, buf, zbr->hash);
	if (err) {
		ubifs_bad_hash(c, buf, zbr->hash, zbr->lnum, zbr->offs);
		return err;
	}

	len = le32_to_cpu(ch->len);
	if (len != zbr->len) {
		ubifs_err(c, "bad node length %d, expected %d", len, zbr->len);
		goto out_err;
	}

	/* Make sure the key of the read node is correct */
	key_read(c, buf + UBIFS_KEY_OFFSET, &key1);
	if (!keys_eq(c, &zbr->key, &key1)) {
		ubifs_err(c, "bad key in node at LEB %d:%d",
			  zbr->lnum, zbr->offs);
		dbg_tnck(&zbr->key, "looked for key ");
		dbg_tnck(&key1, "found node's key ");
		goto out_err;
	}

	return 0;

out_err:
	err = -EINVAL;
out:
	ubifs_err(c, "bad node at LEB %d:%d", zbr->lnum, zbr->offs);
	ubifs_dump_node(c, buf);
	dump_stack();
	return err;
}