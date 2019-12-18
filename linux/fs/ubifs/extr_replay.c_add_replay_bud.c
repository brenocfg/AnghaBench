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
struct ubifs_info {int /*<<< orphan*/  replay_buds; int /*<<< orphan*/  log_hash; } ;
struct ubifs_bud {int lnum; int start; int jhead; unsigned long long sqnum; int /*<<< orphan*/  list; struct ubifs_bud* bud; int /*<<< orphan*/  log_hash; } ;
struct bud_entry {int lnum; int start; int jhead; unsigned long long sqnum; int /*<<< orphan*/  list; struct bud_entry* bud; int /*<<< orphan*/  log_hash; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_mnt (char*,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct ubifs_bud*) ; 
 struct ubifs_bud* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_add_bud (struct ubifs_info*,struct ubifs_bud*) ; 
 int /*<<< orphan*/  ubifs_hash_get_desc (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_shash_copy_state (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_replay_bud(struct ubifs_info *c, int lnum, int offs, int jhead,
			  unsigned long long sqnum)
{
	struct ubifs_bud *bud;
	struct bud_entry *b;
	int err;

	dbg_mnt("add replay bud LEB %d:%d, head %d", lnum, offs, jhead);

	bud = kmalloc(sizeof(struct ubifs_bud), GFP_KERNEL);
	if (!bud)
		return -ENOMEM;

	b = kmalloc(sizeof(struct bud_entry), GFP_KERNEL);
	if (!b) {
		err = -ENOMEM;
		goto out;
	}

	bud->lnum = lnum;
	bud->start = offs;
	bud->jhead = jhead;
	bud->log_hash = ubifs_hash_get_desc(c);
	if (IS_ERR(bud->log_hash)) {
		err = PTR_ERR(bud->log_hash);
		goto out;
	}

	ubifs_shash_copy_state(c, c->log_hash, bud->log_hash);

	ubifs_add_bud(c, bud);

	b->bud = bud;
	b->sqnum = sqnum;
	list_add_tail(&b->list, &c->replay_buds);

	return 0;
out:
	kfree(bud);
	kfree(b);

	return err;
}