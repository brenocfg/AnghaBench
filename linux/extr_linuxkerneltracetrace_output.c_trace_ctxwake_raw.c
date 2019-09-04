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
struct trace_iterator {int /*<<< orphan*/  seq; int /*<<< orphan*/  ent; } ;
struct ctx_switch_entry {int /*<<< orphan*/  next_prio; int /*<<< orphan*/  next_pid; int /*<<< orphan*/  next_cpu; int /*<<< orphan*/  prev_prio; int /*<<< orphan*/  prev_pid; int /*<<< orphan*/  next_state; int /*<<< orphan*/  prev_state; } ;

/* Variables and functions */
 void* task_index_to_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_assign_type (struct ctx_switch_entry*,int /*<<< orphan*/ ) ; 
 int trace_handle_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_seq_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int trace_ctxwake_raw(struct trace_iterator *iter, char S)
{
	struct ctx_switch_entry *field;
	int T;

	trace_assign_type(field, iter->ent);

	if (!S)
		S = task_index_to_char(field->prev_state);
	T = task_index_to_char(field->next_state);
	trace_seq_printf(&iter->seq, "%d %d %c %d %d %d %c\n",
			 field->prev_pid,
			 field->prev_prio,
			 S,
			 field->next_cpu,
			 field->next_pid,
			 field->next_prio,
			 T);

	return trace_handle_return(&iter->seq);
}