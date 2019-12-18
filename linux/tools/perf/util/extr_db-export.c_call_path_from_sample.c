#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  callchain; } ;
struct machine {int dummy; } ;
struct evsel {int dummy; } ;
struct db_export {TYPE_4__* cpr; } ;
struct callchain_cursor_node {int /*<<< orphan*/  ip; TYPE_1__* map; scalar_t__ sym; } ;
struct call_path {int dummy; } ;
struct addr_location {scalar_t__ sym; int /*<<< orphan*/  addr; TYPE_1__* map; struct machine* machine; } ;
typedef  enum chain_order { ____Placeholder_chain_order } chain_order ;
typedef  int /*<<< orphan*/  al ;
struct TYPE_8__ {struct call_path call_path; } ;
struct TYPE_7__ {int order; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_callchain; } ;
struct TYPE_5__ {int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 int ORDER_CALLER ; 
 int /*<<< orphan*/  PERF_MAX_STACK_DEPTH ; 
 struct call_path* call_path__findnew (TYPE_4__*,struct call_path*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor ; 
 int /*<<< orphan*/  callchain_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_cursor_commit (int /*<<< orphan*/ *) ; 
 struct callchain_cursor_node* callchain_cursor_current (int /*<<< orphan*/ *) ; 
 TYPE_3__ callchain_param ; 
 int /*<<< orphan*/  db_ids_from_al (struct db_export*,struct addr_location*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dso__find_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine__kernel_start (struct machine*) ; 
 int /*<<< orphan*/  memset (struct addr_location*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ symbol_conf ; 
 int thread__resolve_callchain (struct thread*,int /*<<< orphan*/ *,struct evsel*,struct perf_sample*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct call_path *call_path_from_sample(struct db_export *dbe,
					       struct machine *machine,
					       struct thread *thread,
					       struct perf_sample *sample,
					       struct evsel *evsel)
{
	u64 kernel_start = machine__kernel_start(machine);
	struct call_path *current = &dbe->cpr->call_path;
	enum chain_order saved_order = callchain_param.order;
	int err;

	if (!symbol_conf.use_callchain || !sample->callchain)
		return NULL;

	/*
	 * Since the call path tree must be built starting with the root, we
	 * must use ORDER_CALL for call chain resolution, in order to process
	 * the callchain starting with the root node and ending with the leaf.
	 */
	callchain_param.order = ORDER_CALLER;
	err = thread__resolve_callchain(thread, &callchain_cursor, evsel,
					sample, NULL, NULL, PERF_MAX_STACK_DEPTH);
	if (err) {
		callchain_param.order = saved_order;
		return NULL;
	}
	callchain_cursor_commit(&callchain_cursor);

	while (1) {
		struct callchain_cursor_node *node;
		struct addr_location al;
		u64 dso_db_id = 0, sym_db_id = 0, offset = 0;

		memset(&al, 0, sizeof(al));

		node = callchain_cursor_current(&callchain_cursor);
		if (!node)
			break;
		/*
		 * Handle export of symbol and dso for this node by
		 * constructing an addr_location struct and then passing it to
		 * db_ids_from_al() to perform the export.
		 */
		al.sym = node->sym;
		al.map = node->map;
		al.machine = machine;
		al.addr = node->ip;

		if (al.map && !al.sym)
			al.sym = dso__find_symbol(al.map->dso, al.addr);

		db_ids_from_al(dbe, &al, &dso_db_id, &sym_db_id, &offset);

		/* add node to the call path tree if it doesn't exist */
		current = call_path__findnew(dbe->cpr, current,
					     al.sym, node->ip,
					     kernel_start);

		callchain_cursor_advance(&callchain_cursor);
	}

	/* Reset the callchain order to its prior value. */
	callchain_param.order = saved_order;

	if (current == &dbe->cpr->call_path) {
		/* Bail because the callchain was empty. */
		return NULL;
	}

	return current;
}