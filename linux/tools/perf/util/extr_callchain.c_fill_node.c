#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct callchain_node {int /*<<< orphan*/  val; scalar_t__ val_nr; } ;
struct TYPE_5__ {int branch_to; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; int /*<<< orphan*/  sym; } ;
struct callchain_list {int branch_count; int predicted_count; int abort_count; int /*<<< orphan*/  list; int /*<<< orphan*/  iter_cycles; int /*<<< orphan*/  iter_count; int /*<<< orphan*/  cycles_count; TYPE_2__ brtype_stat; int /*<<< orphan*/  srcline; TYPE_1__ ms; int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  cycles; scalar_t__ abort; scalar_t__ predicted; } ;
struct callchain_cursor_node {int /*<<< orphan*/  iter_cycles; int /*<<< orphan*/  nr_loop_iter; TYPE_3__ branch_flags; int /*<<< orphan*/  ip; int /*<<< orphan*/  branch_from; scalar_t__ branch; int /*<<< orphan*/  srcline; int /*<<< orphan*/  map; int /*<<< orphan*/  sym; } ;
struct callchain_cursor {scalar_t__ pos; scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  branch_type_count (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor_advance (struct callchain_cursor*) ; 
 struct callchain_cursor_node* callchain_cursor_current (struct callchain_cursor*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 struct callchain_list* zalloc (int) ; 

__attribute__((used)) static int
fill_node(struct callchain_node *node, struct callchain_cursor *cursor)
{
	struct callchain_cursor_node *cursor_node;

	node->val_nr = cursor->nr - cursor->pos;
	if (!node->val_nr)
		pr_warning("Warning: empty node in callchain tree\n");

	cursor_node = callchain_cursor_current(cursor);

	while (cursor_node) {
		struct callchain_list *call;

		call = zalloc(sizeof(*call));
		if (!call) {
			perror("not enough memory for the code path tree");
			return -1;
		}
		call->ip = cursor_node->ip;
		call->ms.sym = cursor_node->sym;
		call->ms.map = map__get(cursor_node->map);
		call->srcline = cursor_node->srcline;

		if (cursor_node->branch) {
			call->branch_count = 1;

			if (cursor_node->branch_from) {
				/*
				 * branch_from is set with value somewhere else
				 * to imply it's "to" of a branch.
				 */
				call->brtype_stat.branch_to = true;

				if (cursor_node->branch_flags.predicted)
					call->predicted_count = 1;

				if (cursor_node->branch_flags.abort)
					call->abort_count = 1;

				branch_type_count(&call->brtype_stat,
						  &cursor_node->branch_flags,
						  cursor_node->branch_from,
						  cursor_node->ip);
			} else {
				/*
				 * It's "from" of a branch
				 */
				call->brtype_stat.branch_to = false;
				call->cycles_count =
					cursor_node->branch_flags.cycles;
				call->iter_count = cursor_node->nr_loop_iter;
				call->iter_cycles = cursor_node->iter_cycles;
			}
		}

		list_add_tail(&call->list, &node->val);

		callchain_cursor_advance(cursor);
		cursor_node = callchain_cursor_current(cursor);
	}
	return 0;
}