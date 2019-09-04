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
struct ocfs2_reservation_map {int /*<<< orphan*/  m_lru; } ;
struct ocfs2_alloc_reservation {int /*<<< orphan*/  r_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resv_lock ; 

__attribute__((used)) static void ocfs2_resv_mark_lru(struct ocfs2_reservation_map *resmap,
				struct ocfs2_alloc_reservation *resv)
{
	assert_spin_locked(&resv_lock);

	if (!list_empty(&resv->r_lru))
		list_del_init(&resv->r_lru);

	list_add_tail(&resv->r_lru, &resmap->m_lru);
}