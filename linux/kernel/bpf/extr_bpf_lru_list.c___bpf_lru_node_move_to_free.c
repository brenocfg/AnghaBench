#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_2__ {struct TYPE_2__* prev; } ;
struct bpf_lru_node {int type; TYPE_1__ list; } ;
struct bpf_lru_list {TYPE_1__* next_inactive_rotation; } ;
typedef  enum bpf_lru_list_type { ____Placeholder_bpf_lru_list_type } bpf_lru_list_type ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LOCAL_LIST_TYPE (int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_lru_list_count_dec (struct bpf_lru_list*,int) ; 
 int /*<<< orphan*/  list_move (TYPE_1__*,struct list_head*) ; 

__attribute__((used)) static void __bpf_lru_node_move_to_free(struct bpf_lru_list *l,
					struct bpf_lru_node *node,
					struct list_head *free_list,
					enum bpf_lru_list_type tgt_free_type)
{
	if (WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(node->type)))
		return;

	/* If the removing node is the next_inactive_rotation candidate,
	 * move the next_inactive_rotation pointer also.
	 */
	if (&node->list == l->next_inactive_rotation)
		l->next_inactive_rotation = l->next_inactive_rotation->prev;

	bpf_lru_list_count_dec(l, node->type);

	node->type = tgt_free_type;
	list_move(&node->list, free_list);
}