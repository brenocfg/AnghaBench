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
struct ubifs_info {scalar_t__ need_recovery; } ;
struct replay_entry {int /*<<< orphan*/  new_size; scalar_t__ deletion; int /*<<< orphan*/  key; int /*<<< orphan*/  hash; int /*<<< orphan*/  len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; int /*<<< orphan*/  nm; int /*<<< orphan*/  sqnum; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
#define  UBIFS_INO_KEY 129 
#define  UBIFS_TRUN_KEY 128 
 int /*<<< orphan*/  dbg_mntk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_still_linked (struct ubifs_info*,struct replay_entry*) ; 
 scalar_t__ is_hash_key (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_inum (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int key_type (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int trun_remove_range (struct ubifs_info*,struct replay_entry*) ; 
 int ubifs_recover_size_accum (struct ubifs_info*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int ubifs_tnc_add (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_tnc_add_nm (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ubifs_tnc_remove (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int ubifs_tnc_remove_ino (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_tnc_remove_nm (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_replay_entry(struct ubifs_info *c, struct replay_entry *r)
{
	int err;

	dbg_mntk(&r->key, "LEB %d:%d len %d deletion %d sqnum %llu key ",
		 r->lnum, r->offs, r->len, r->deletion, r->sqnum);

	if (is_hash_key(c, &r->key)) {
		if (r->deletion)
			err = ubifs_tnc_remove_nm(c, &r->key, &r->nm);
		else
			err = ubifs_tnc_add_nm(c, &r->key, r->lnum, r->offs,
					       r->len, r->hash, &r->nm);
	} else {
		if (r->deletion)
			switch (key_type(c, &r->key)) {
			case UBIFS_INO_KEY:
			{
				ino_t inum = key_inum(c, &r->key);

				if (inode_still_linked(c, r)) {
					err = 0;
					break;
				}

				err = ubifs_tnc_remove_ino(c, inum);
				break;
			}
			case UBIFS_TRUN_KEY:
				err = trun_remove_range(c, r);
				break;
			default:
				err = ubifs_tnc_remove(c, &r->key);
				break;
			}
		else
			err = ubifs_tnc_add(c, &r->key, r->lnum, r->offs,
					    r->len, r->hash);
		if (err)
			return err;

		if (c->need_recovery)
			err = ubifs_recover_size_accum(c, &r->key, r->deletion,
						       r->new_size);
	}

	return err;
}