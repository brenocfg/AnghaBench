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
struct ocfs2_reservation_map {int dummy; } ;
struct ocfs2_alloc_reservation {scalar_t__ r_last_start; scalar_t__ r_last_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocfs2_resv_trunc (struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_resv_remove (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  resv_lock ; 

__attribute__((used)) static void __ocfs2_resv_discard(struct ocfs2_reservation_map *resmap,
				 struct ocfs2_alloc_reservation *resv)
{
	assert_spin_locked(&resv_lock);

	__ocfs2_resv_trunc(resv);
	/*
	 * last_len and last_start no longer make sense if
	 * we're changing the range of our allocations.
	 */
	resv->r_last_len = resv->r_last_start = 0;

	ocfs2_resv_remove(resmap, resv);
}