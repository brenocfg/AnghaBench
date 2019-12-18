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
struct bpf_lru_node {int type; int /*<<< orphan*/  list; scalar_t__ ref; } ;
struct bpf_lru_list {int /*<<< orphan*/ * lists; } ;
typedef  enum bpf_lru_list_type { ____Placeholder_bpf_lru_list_type } bpf_lru_list_type ;

/* Variables and functions */
 int IS_LOCAL_LIST_TYPE (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bpf_lru_list_count_inc (struct bpf_lru_list*,int) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bpf_lru_node_move_in(struct bpf_lru_list *l,
				   struct bpf_lru_node *node,
				   enum bpf_lru_list_type tgt_type)
{
	if (WARN_ON_ONCE(!IS_LOCAL_LIST_TYPE(node->type)) ||
	    WARN_ON_ONCE(IS_LOCAL_LIST_TYPE(tgt_type)))
		return;

	bpf_lru_list_count_inc(l, tgt_type);
	node->type = tgt_type;
	node->ref = 0;
	list_move(&node->list, &l->lists[tgt_type]);
}