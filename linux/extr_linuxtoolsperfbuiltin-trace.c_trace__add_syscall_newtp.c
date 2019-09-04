#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct perf_evsel* sys_exit; struct perf_evsel* sys_enter; } ;
struct TYPE_8__ {TYPE_2__ events; } ;
struct trace {TYPE_3__ syscalls; int /*<<< orphan*/  kernel_syscallchains; int /*<<< orphan*/  opts; struct perf_evlist* evlist; } ;
struct TYPE_6__ {int exclude_callchain_kernel; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int dummy; } ;
struct TYPE_9__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  args ; 
 TYPE_4__ callchain_param ; 
 int /*<<< orphan*/  perf_evlist__add (struct perf_evlist*,struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__config_callchain (struct perf_evsel*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  perf_evsel__delete_priv (struct perf_evsel*) ; 
 scalar_t__ perf_evsel__init_sc_tp_ptr_field (struct perf_evsel*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evsel__init_sc_tp_uint_field (struct perf_evsel*,int) ; 
 struct perf_evsel* perf_evsel__raw_syscall_newtp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace__sys_enter ; 
 int /*<<< orphan*/  trace__sys_exit ; 

__attribute__((used)) static int trace__add_syscall_newtp(struct trace *trace)
{
	int ret = -1;
	struct perf_evlist *evlist = trace->evlist;
	struct perf_evsel *sys_enter, *sys_exit;

	sys_enter = perf_evsel__raw_syscall_newtp("sys_enter", trace__sys_enter);
	if (sys_enter == NULL)
		goto out;

	if (perf_evsel__init_sc_tp_ptr_field(sys_enter, args))
		goto out_delete_sys_enter;

	sys_exit = perf_evsel__raw_syscall_newtp("sys_exit", trace__sys_exit);
	if (sys_exit == NULL)
		goto out_delete_sys_enter;

	if (perf_evsel__init_sc_tp_uint_field(sys_exit, ret))
		goto out_delete_sys_exit;

	perf_evsel__config_callchain(sys_enter, &trace->opts, &callchain_param);
	perf_evsel__config_callchain(sys_exit, &trace->opts, &callchain_param);

	perf_evlist__add(evlist, sys_enter);
	perf_evlist__add(evlist, sys_exit);

	if (callchain_param.enabled && !trace->kernel_syscallchains) {
		/*
		 * We're interested only in the user space callchain
		 * leading to the syscall, allow overriding that for
		 * debugging reasons using --kernel_syscall_callchains
		 */
		sys_exit->attr.exclude_callchain_kernel = 1;
	}

	trace->syscalls.events.sys_enter = sys_enter;
	trace->syscalls.events.sys_exit  = sys_exit;

	ret = 0;
out:
	return ret;

out_delete_sys_exit:
	perf_evsel__delete_priv(sys_exit);
out_delete_sys_enter:
	perf_evsel__delete_priv(sys_enter);
	goto out;
}