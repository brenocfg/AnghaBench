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
typedef  void* u64 ;
struct thread_stack_entry {int no_call; int trace_end; int non_call; scalar_t__ db_id; struct call_path* cp; int /*<<< orphan*/  cyc_count; int /*<<< orphan*/  insn_count; int /*<<< orphan*/  branch_count; void* ref; void* timestamp; void* ret_addr; } ;
struct thread_stack {scalar_t__ cnt; scalar_t__ sz; int /*<<< orphan*/  cyc_count; int /*<<< orphan*/  insn_count; int /*<<< orphan*/  branch_count; struct thread_stack_entry* stack; } ;
struct call_path {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int thread_stack__grow (struct thread_stack*) ; 

__attribute__((used)) static int thread_stack__push_cp(struct thread_stack *ts, u64 ret_addr,
				 u64 timestamp, u64 ref, struct call_path *cp,
				 bool no_call, bool trace_end)
{
	struct thread_stack_entry *tse;
	int err;

	if (!cp)
		return -ENOMEM;

	if (ts->cnt == ts->sz) {
		err = thread_stack__grow(ts);
		if (err)
			return err;
	}

	tse = &ts->stack[ts->cnt++];
	tse->ret_addr = ret_addr;
	tse->timestamp = timestamp;
	tse->ref = ref;
	tse->branch_count = ts->branch_count;
	tse->insn_count = ts->insn_count;
	tse->cyc_count = ts->cyc_count;
	tse->cp = cp;
	tse->no_call = no_call;
	tse->trace_end = trace_end;
	tse->non_call = false;
	tse->db_id = 0;

	return 0;
}