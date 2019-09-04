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
typedef  int uint32_t ;
struct jffs2_sb_info {int nr_erasing_blocks; int nr_free_blocks; int /*<<< orphan*/  free_list; int /*<<< orphan*/  erase_pending_list; int /*<<< orphan*/  erasable_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  very_dirty_list; int /*<<< orphan*/  clean_list; } ;

/* Variables and functions */
 int count_list (int /*<<< orphan*/ *) ; 
 int pseudo_random ; 
 int /*<<< orphan*/  rotate_list (int /*<<< orphan*/ *,int) ; 

void jffs2_rotate_lists(struct jffs2_sb_info *c)
{
	uint32_t x;
	uint32_t rotateby;

	x = count_list(&c->clean_list);
	if (x) {
		rotateby = pseudo_random % x;
		rotate_list((&c->clean_list), rotateby);
	}

	x = count_list(&c->very_dirty_list);
	if (x) {
		rotateby = pseudo_random % x;
		rotate_list((&c->very_dirty_list), rotateby);
	}

	x = count_list(&c->dirty_list);
	if (x) {
		rotateby = pseudo_random % x;
		rotate_list((&c->dirty_list), rotateby);
	}

	x = count_list(&c->erasable_list);
	if (x) {
		rotateby = pseudo_random % x;
		rotate_list((&c->erasable_list), rotateby);
	}

	if (c->nr_erasing_blocks) {
		rotateby = pseudo_random % c->nr_erasing_blocks;
		rotate_list((&c->erase_pending_list), rotateby);
	}

	if (c->nr_free_blocks) {
		rotateby = pseudo_random % c->nr_free_blocks;
		rotate_list((&c->free_list), rotateby);
	}
}