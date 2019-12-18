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
struct thread_stack_entry {void* db_id; scalar_t__ non_call; scalar_t__ no_call; int /*<<< orphan*/  ref; scalar_t__ cyc_count; scalar_t__ insn_count; scalar_t__ branch_count; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  cp; } ;
struct thread_stack {scalar_t__ cyc_count; scalar_t__ insn_count; scalar_t__ branch_count; struct thread_stack_entry* stack; int /*<<< orphan*/  comm; struct call_return_processor* crp; } ;
struct thread {int dummy; } ;
struct call_return_processor {int (* process ) (struct call_return*,void**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct call_return {void* db_id; int /*<<< orphan*/  flags; void* return_ref; int /*<<< orphan*/  call_ref; scalar_t__ cyc_count; scalar_t__ insn_count; scalar_t__ branch_count; void* return_time; int /*<<< orphan*/  call_time; int /*<<< orphan*/  cp; int /*<<< orphan*/  comm; struct thread* thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_RETURN_NON_CALL ; 
 int /*<<< orphan*/  CALL_RETURN_NO_CALL ; 
 int /*<<< orphan*/  CALL_RETURN_NO_RETURN ; 
 int stub1 (struct call_return*,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thread_stack__call_return(struct thread *thread,
				     struct thread_stack *ts, size_t idx,
				     u64 timestamp, u64 ref, bool no_return)
{
	struct call_return_processor *crp = ts->crp;
	struct thread_stack_entry *tse;
	struct call_return cr = {
		.thread = thread,
		.comm = ts->comm,
		.db_id = 0,
	};
	u64 *parent_db_id;

	tse = &ts->stack[idx];
	cr.cp = tse->cp;
	cr.call_time = tse->timestamp;
	cr.return_time = timestamp;
	cr.branch_count = ts->branch_count - tse->branch_count;
	cr.insn_count = ts->insn_count - tse->insn_count;
	cr.cyc_count = ts->cyc_count - tse->cyc_count;
	cr.db_id = tse->db_id;
	cr.call_ref = tse->ref;
	cr.return_ref = ref;
	if (tse->no_call)
		cr.flags |= CALL_RETURN_NO_CALL;
	if (no_return)
		cr.flags |= CALL_RETURN_NO_RETURN;
	if (tse->non_call)
		cr.flags |= CALL_RETURN_NON_CALL;

	/*
	 * The parent db_id must be assigned before exporting the child. Note
	 * it is not possible to export the parent first because its information
	 * is not yet complete because its 'return' has not yet been processed.
	 */
	parent_db_id = idx ? &(tse - 1)->db_id : NULL;

	return crp->process(&cr, parent_db_id, crp->data);
}