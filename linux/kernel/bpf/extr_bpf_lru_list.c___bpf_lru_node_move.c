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
struct TYPE_2__ {struct TYPE_2__* prev; } ;
struct bpf_lru_node {int type; TYPE_1__ list; scalar_t__ ref; } ;
struct bpf_lru_list {int /*<<< orphan*/ * lists; TYPE_1__* next_inactive_rotation; } ;
typedef  enum bpf_lru_list_type { ____Placeholder_bpf_lru_list_type } bpf_lru_list_type ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LOCAL_LIST_TYPE (int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_lru_list_count_dec (struct bpf_lru_list*,int) ; 
 int /*<<< orphan*/  bpf_lru_list_count_inc (struct bpf_lru_list*,int) ; 
 int /*<<< orphan*/  list_move (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bpf_lru_node_move(struct bpf_lru_list *l,
				struct bpf_lru_node *node,
				enum bpf_lru_list_type tgt_type)
{
	if (WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(node->type)) ||
	    WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(tgt_type)))
		return;

	if (node->type != tgt_type) {
		bpf_lru_list_count_dec(l, node->type);
		bpf_lru_list_count_inc(l, tgt_type);
		node->type = tgt_type;
	}
	node->ref = 0;

	/* If the moving node is the next_inactive_rotation candidate,
	 * move the next_inactive_rotation pointer also.
	 */
	if (&node->list == l->next_inactive_rotation)
		l->next_inactive_rotation = l->next_inactive_rotation->prev;

	list_move(&node->list, &l->lists[tgt_type]);
}