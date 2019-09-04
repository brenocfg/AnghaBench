#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int branch_to; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; TYPE_1__* sym; } ;
struct callchain_list {int /*<<< orphan*/  from_count; int /*<<< orphan*/  iter_cycles; int /*<<< orphan*/  iter_count; int /*<<< orphan*/  cycles_count; TYPE_5__ brtype_stat; int /*<<< orphan*/  abort_count; int /*<<< orphan*/  predicted_count; int /*<<< orphan*/  branch_count; int /*<<< orphan*/  ip; TYPE_3__ ms; int /*<<< orphan*/  srcline; } ;
struct TYPE_12__ {scalar_t__ cycles; scalar_t__ abort; scalar_t__ predicted; } ;
struct callchain_cursor_node {scalar_t__ iter_cycles; scalar_t__ nr_loop_iter; TYPE_6__ branch_flags; int /*<<< orphan*/  ip; scalar_t__ branch_from; scalar_t__ branch; int /*<<< orphan*/  map; TYPE_2__* sym; int /*<<< orphan*/  srcline; } ;
typedef  enum match_result { ____Placeholder_match_result } match_result ;
struct TYPE_10__ {int key; } ;
struct TYPE_8__ {int /*<<< orphan*/  start; int /*<<< orphan*/  name; int /*<<< orphan*/  inlined; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; int /*<<< orphan*/  name; int /*<<< orphan*/  inlined; } ;

/* Variables and functions */
#define  CCKEY_ADDRESS 130 
#define  CCKEY_FUNCTION 129 
#define  CCKEY_SRCLINE 128 
 int MATCH_EQ ; 
 int MATCH_ERROR ; 
 int /*<<< orphan*/  __fallthrough ; 
 int /*<<< orphan*/  branch_type_count (TYPE_5__*,TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__ callchain_param ; 
 int match_chain_dso_addresses (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int match_chain_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum match_result match_chain(struct callchain_cursor_node *node,
				     struct callchain_list *cnode)
{
	enum match_result match = MATCH_ERROR;

	switch (callchain_param.key) {
	case CCKEY_SRCLINE:
		match = match_chain_strings(cnode->srcline, node->srcline);
		if (match != MATCH_ERROR)
			break;
		/* otherwise fall-back to symbol-based comparison below */
		__fallthrough;
	case CCKEY_FUNCTION:
		if (node->sym && cnode->ms.sym) {
			/*
			 * Compare inlined frames based on their symbol name
			 * because different inlined frames will have the same
			 * symbol start. Otherwise do a faster comparison based
			 * on the symbol start address.
			 */
			if (cnode->ms.sym->inlined || node->sym->inlined) {
				match = match_chain_strings(cnode->ms.sym->name,
							    node->sym->name);
				if (match != MATCH_ERROR)
					break;
			} else {
				match = match_chain_dso_addresses(cnode->ms.map, cnode->ms.sym->start,
								  node->map, node->sym->start);
				break;
			}
		}
		/* otherwise fall-back to IP-based comparison below */
		__fallthrough;
	case CCKEY_ADDRESS:
	default:
		match = match_chain_dso_addresses(cnode->ms.map, cnode->ip, node->map, node->ip);
		break;
	}

	if (match == MATCH_EQ && node->branch) {
		cnode->branch_count++;

		if (node->branch_from) {
			/*
			 * It's "to" of a branch
			 */
			cnode->brtype_stat.branch_to = true;

			if (node->branch_flags.predicted)
				cnode->predicted_count++;

			if (node->branch_flags.abort)
				cnode->abort_count++;

			branch_type_count(&cnode->brtype_stat,
					  &node->branch_flags,
					  node->branch_from,
					  node->ip);
		} else {
			/*
			 * It's "from" of a branch
			 */
			cnode->brtype_stat.branch_to = false;
			cnode->cycles_count += node->branch_flags.cycles;
			cnode->iter_count += node->nr_loop_iter;
			cnode->iter_cycles += node->iter_cycles;
			cnode->from_count++;
		}
	}

	return match;
}