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
struct swap_cluster_info {int dummy; } ;
struct swap_cluster_list {struct swap_cluster_info head; struct swap_cluster_info tail; } ;

/* Variables and functions */
 unsigned int cluster_next (struct swap_cluster_info*) ; 
 int /*<<< orphan*/  cluster_set_next_flag (struct swap_cluster_info*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_set_null (struct swap_cluster_info*) ; 

__attribute__((used)) static unsigned int cluster_list_del_first(struct swap_cluster_list *list,
					   struct swap_cluster_info *ci)
{
	unsigned int idx;

	idx = cluster_next(&list->head);
	if (cluster_next(&list->tail) == idx) {
		cluster_set_null(&list->head);
		cluster_set_null(&list->tail);
	} else
		cluster_set_next_flag(&list->head,
				      cluster_next(&ci[idx]), 0);

	return idx;
}