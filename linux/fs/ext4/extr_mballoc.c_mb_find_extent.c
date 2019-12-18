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
struct ext4_free_extent {int fe_len; int fe_start; int /*<<< orphan*/  fe_group; int /*<<< orphan*/  fe_logical; } ;
struct ext4_buddy {void* bd_bitmap; int /*<<< orphan*/  bd_sb; int /*<<< orphan*/  bd_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXT4_CLUSTERS_PER_GROUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_group_lock_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mb_find_buddy (struct ext4_buddy*,int,int*) ; 
 int mb_find_order_for_block (struct ext4_buddy*,int) ; 
 scalar_t__ mb_test_bit (int,void*) ; 

__attribute__((used)) static int mb_find_extent(struct ext4_buddy *e4b, int block,
				int needed, struct ext4_free_extent *ex)
{
	int next = block;
	int max, order;
	void *buddy;

	assert_spin_locked(ext4_group_lock_ptr(e4b->bd_sb, e4b->bd_group));
	BUG_ON(ex == NULL);

	buddy = mb_find_buddy(e4b, 0, &max);
	BUG_ON(buddy == NULL);
	BUG_ON(block >= max);
	if (mb_test_bit(block, buddy)) {
		ex->fe_len = 0;
		ex->fe_start = 0;
		ex->fe_group = 0;
		return 0;
	}

	/* find actual order */
	order = mb_find_order_for_block(e4b, block);
	block = block >> order;

	ex->fe_len = 1 << order;
	ex->fe_start = block << order;
	ex->fe_group = e4b->bd_group;

	/* calc difference from given start */
	next = next - ex->fe_start;
	ex->fe_len -= next;
	ex->fe_start += next;

	while (needed > ex->fe_len &&
	       mb_find_buddy(e4b, order, &max)) {

		if (block + 1 >= max)
			break;

		next = (block + 1) * (1 << order);
		if (mb_test_bit(next, e4b->bd_bitmap))
			break;

		order = mb_find_order_for_block(e4b, next);

		block = next >> order;
		ex->fe_len += 1 << order;
	}

	if (ex->fe_start + ex->fe_len > EXT4_CLUSTERS_PER_GROUP(e4b->bd_sb)) {
		/* Should never happen! (but apparently sometimes does?!?) */
		WARN_ON(1);
		ext4_error(e4b->bd_sb, "corruption or bug in mb_find_extent "
			   "block=%d, order=%d needed=%d ex=%u/%d/%d@%u",
			   block, order, needed, ex->fe_group, ex->fe_start,
			   ex->fe_len, ex->fe_logical);
		ex->fe_len = 0;
		ex->fe_start = 0;
		ex->fe_group = 0;
	}
	return ex->fe_len;
}