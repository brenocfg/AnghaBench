#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int (* unwind_entry_cb_t ) (TYPE_2__*,void*) ;
typedef  int /*<<< orphan*/  ui_buf ;
struct unwind_info {int (* cb ) (TYPE_2__*,void*) ;void* arg; int max_stack; int idx; int /*<<< orphan*/  dwfl; TYPE_2__* entries; int /*<<< orphan*/  machine; struct thread* thread; struct perf_sample* sample; } ;
struct thread {int /*<<< orphan*/  tid; TYPE_1__* mg; } ;
struct TYPE_9__ {int /*<<< orphan*/  regs; } ;
struct perf_sample {TYPE_5__ user_regs; } ;
struct TYPE_10__ {scalar_t__ order; } ;
struct TYPE_8__ {scalar_t__ ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  machine; } ;
typedef  int /*<<< orphan*/  Dwarf_Word ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EM_NONE ; 
 int ENOMEM ; 
 scalar_t__ ORDER_CALLER ; 
 int /*<<< orphan*/  PERF_REG_IP ; 
 int /*<<< orphan*/  callbacks ; 
 TYPE_6__ callchain_param ; 
 int /*<<< orphan*/  dwfl_attach_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct unwind_info*) ; 
 int /*<<< orphan*/  dwfl_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwfl_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwfl_errmsg (int) ; 
 int dwfl_getthread_frames (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct unwind_info*) ; 
 int /*<<< orphan*/  frame_callback ; 
 int /*<<< orphan*/  free (struct unwind_info*) ; 
 int /*<<< orphan*/  offline_callbacks ; 
 int perf_reg_value (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int report_module (int /*<<< orphan*/ ,struct unwind_info*) ; 
 int stub1 (TYPE_2__*,void*) ; 
 struct unwind_info* zalloc (int) ; 

int unwind__get_entries(unwind_entry_cb_t cb, void *arg,
			struct thread *thread,
			struct perf_sample *data,
			int max_stack)
{
	struct unwind_info *ui, ui_buf = {
		.sample		= data,
		.thread		= thread,
		.machine	= thread->mg->machine,
		.cb		= cb,
		.arg		= arg,
		.max_stack	= max_stack,
	};
	Dwarf_Word ip;
	int err = -EINVAL, i;

	if (!data->user_regs.regs)
		return -EINVAL;

	ui = zalloc(sizeof(ui_buf) + sizeof(ui_buf.entries[0]) * max_stack);
	if (!ui)
		return -ENOMEM;

	*ui = ui_buf;

	ui->dwfl = dwfl_begin(&offline_callbacks);
	if (!ui->dwfl)
		goto out;

	err = perf_reg_value(&ip, &data->user_regs, PERF_REG_IP);
	if (err)
		goto out;

	err = report_module(ip, ui);
	if (err)
		goto out;

	err = !dwfl_attach_state(ui->dwfl, EM_NONE, thread->tid, &callbacks, ui);
	if (err)
		goto out;

	err = dwfl_getthread_frames(ui->dwfl, thread->tid, frame_callback, ui);

	if (err && ui->max_stack != max_stack)
		err = 0;

	/*
	 * Display what we got based on the order setup.
	 */
	for (i = 0; i < ui->idx && !err; i++) {
		int j = i;

		if (callchain_param.order == ORDER_CALLER)
			j = ui->idx - i - 1;

		err = ui->entries[j].ip ? ui->cb(&ui->entries[j], ui->arg) : 0;
	}

 out:
	if (err)
		pr_debug("unwind: failed with '%s'\n", dwfl_errmsg(-1));

	dwfl_end(ui->dwfl);
	free(ui);
	return 0;
}