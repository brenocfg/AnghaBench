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
struct swap_cluster_list {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct swap_cluster_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ cluster_list_empty (struct swap_cluster_list*) ; 
 unsigned int cluster_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_set_next (struct swap_cluster_info*,unsigned int) ; 
 int /*<<< orphan*/  cluster_set_next_flag (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cluster_list_add_tail(struct swap_cluster_list *list,
				  struct swap_cluster_info *ci,
				  unsigned int idx)
{
	if (cluster_list_empty(list)) {
		cluster_set_next_flag(&list->head, idx, 0);
		cluster_set_next_flag(&list->tail, idx, 0);
	} else {
		struct swap_cluster_info *ci_tail;
		unsigned int tail = cluster_next(&list->tail);

		/*
		 * Nested cluster lock, but both cluster locks are
		 * only acquired when we held swap_info_struct->lock
		 */
		ci_tail = ci + tail;
		spin_lock_nested(&ci_tail->lock, SINGLE_DEPTH_NESTING);
		cluster_set_next(ci_tail, idx);
		spin_unlock(&ci_tail->lock);
		cluster_set_next_flag(&list->tail, idx, 0);
	}
}