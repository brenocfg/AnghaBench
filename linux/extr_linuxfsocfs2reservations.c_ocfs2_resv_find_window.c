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
struct ocfs2_reservation_map {unsigned int m_bitmap_len; } ;
struct ocfs2_alloc_reservation {int r_last_len; unsigned int r_last_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __ocfs2_resv_find_window (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_cannibalize_resv (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*,unsigned int) ; 
 int ocfs2_resv_empty (struct ocfs2_alloc_reservation*) ; 

__attribute__((used)) static void ocfs2_resv_find_window(struct ocfs2_reservation_map *resmap,
				   struct ocfs2_alloc_reservation *resv,
				   unsigned int wanted)
{
	unsigned int goal = 0;

	BUG_ON(!ocfs2_resv_empty(resv));

	/*
	 * Begin by trying to get a window as close to the previous
	 * one as possible. Using the most recent allocation as a
	 * start goal makes sense.
	 */
	if (resv->r_last_len) {
		goal = resv->r_last_start + resv->r_last_len;
		if (goal >= resmap->m_bitmap_len)
			goal = 0;
	}

	__ocfs2_resv_find_window(resmap, resv, goal, wanted);

	/* Search from last alloc didn't work, try once more from beginning. */
	if (ocfs2_resv_empty(resv) && goal != 0)
		__ocfs2_resv_find_window(resmap, resv, 0, wanted);

	if (ocfs2_resv_empty(resv)) {
		/*
		 * Still empty? Pull oldest one off the LRU, remove it from
		 * tree, put this one in it's place.
		 */
		ocfs2_cannibalize_resv(resmap, resv, wanted);
	}

	BUG_ON(ocfs2_resv_empty(resv));
}