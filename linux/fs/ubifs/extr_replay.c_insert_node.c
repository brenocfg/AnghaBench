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
struct ubifs_info {scalar_t__ highest_inum; int /*<<< orphan*/  replay_list; } ;
struct replay_entry {int lnum; int offs; int len; int deletion; unsigned long long sqnum; int /*<<< orphan*/  list; void* new_size; void* old_size; int /*<<< orphan*/  key; int /*<<< orphan*/  hash; } ;
typedef  void* loff_t ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dbg_mntk (union ubifs_key*,char*,int,int) ; 
 int /*<<< orphan*/  key_copy (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ *) ; 
 scalar_t__ key_inum (struct ubifs_info*,union ubifs_key*) ; 
 struct replay_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_copy_hash (struct ubifs_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_node(struct ubifs_info *c, int lnum, int offs, int len,
		       const u8 *hash, union ubifs_key *key,
		       unsigned long long sqnum, int deletion, int *used,
		       loff_t old_size, loff_t new_size)
{
	struct replay_entry *r;

	dbg_mntk(key, "add LEB %d:%d, key ", lnum, offs);

	if (key_inum(c, key) >= c->highest_inum)
		c->highest_inum = key_inum(c, key);

	r = kzalloc(sizeof(struct replay_entry), GFP_KERNEL);
	if (!r)
		return -ENOMEM;

	if (!deletion)
		*used += ALIGN(len, 8);
	r->lnum = lnum;
	r->offs = offs;
	r->len = len;
	ubifs_copy_hash(c, hash, r->hash);
	r->deletion = !!deletion;
	r->sqnum = sqnum;
	key_copy(c, key, &r->key);
	r->old_size = old_size;
	r->new_size = new_size;

	list_add_tail(&r->list, &c->replay_list);
	return 0;
}