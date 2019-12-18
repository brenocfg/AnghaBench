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
struct reiserfs_key {int dummy; } ;
struct disk_child {int dummy; } ;
struct buffer_info {struct buffer_head* bi_parent; int /*<<< orphan*/  tb; int /*<<< orphan*/  bi_position; struct buffer_head* bi_bh; } ;
struct buffer_head {int dummy; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 int B_FREE_SPACE (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 struct disk_child* B_N_CHILD (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int DC_SIZE ; 
 int KEY_SIZE ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,...) ; 
 scalar_t__ blkh_free_space (struct block_head*) ; 
 int blkh_nr_item (struct block_head*) ; 
 scalar_t__ dc_size (struct disk_child*) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 struct reiserfs_key* internal_key (struct buffer_head*,int) ; 
 int /*<<< orphan*/  memcpy (struct reiserfs_key*,struct reiserfs_key*,int) ; 
 int /*<<< orphan*/  memmove (struct reiserfs_key*,struct reiserfs_key*,int) ; 
 int /*<<< orphan*/  put_dc_size (struct disk_child*,scalar_t__) ; 
 int /*<<< orphan*/  set_blkh_free_space (struct block_head*,scalar_t__) ; 
 int /*<<< orphan*/  set_blkh_nr_item (struct block_head*,int) ; 

__attribute__((used)) static void internal_insert_key(struct buffer_info *dest_bi,
				/* insert key before key with n_dest number */
				int dest_position_before,
				struct buffer_head *src, int src_position)
{
	struct buffer_head *dest = dest_bi->bi_bh;
	int nr;
	struct block_head *blkh;
	struct reiserfs_key *key;

	RFALSE(dest == NULL || src == NULL,
	       "source(%p) or dest(%p) buffer is 0", src, dest);
	RFALSE(dest_position_before < 0 || src_position < 0,
	       "source(%d) or dest(%d) key number less than 0",
	       src_position, dest_position_before);
	RFALSE(dest_position_before > B_NR_ITEMS(dest) ||
	       src_position >= B_NR_ITEMS(src),
	       "invalid position in dest (%d (key number %d)) or in src (%d (key number %d))",
	       dest_position_before, B_NR_ITEMS(dest),
	       src_position, B_NR_ITEMS(src));
	RFALSE(B_FREE_SPACE(dest) < KEY_SIZE,
	       "no enough free space (%d) in dest buffer", B_FREE_SPACE(dest));

	blkh = B_BLK_HEAD(dest);
	nr = blkh_nr_item(blkh);

	/* prepare space for inserting key */
	key = internal_key(dest, dest_position_before);
	memmove(key + 1, key,
		(nr - dest_position_before) * KEY_SIZE + (nr + 1) * DC_SIZE);

	/* insert key */
	memcpy(key, internal_key(src, src_position), KEY_SIZE);

	/* Change dirt, free space, item number fields. */

	set_blkh_nr_item(blkh, blkh_nr_item(blkh) + 1);
	set_blkh_free_space(blkh, blkh_free_space(blkh) - KEY_SIZE);

	do_balance_mark_internal_dirty(dest_bi->tb, dest, 0);

	if (dest_bi->bi_parent) {
		struct disk_child *t_dc;
		t_dc = B_N_CHILD(dest_bi->bi_parent, dest_bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) + KEY_SIZE);

		do_balance_mark_internal_dirty(dest_bi->tb, dest_bi->bi_parent,
					       0);
	}
}