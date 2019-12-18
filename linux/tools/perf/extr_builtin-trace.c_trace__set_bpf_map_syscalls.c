#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* sys_exit; void* sys_enter; } ;
struct TYPE_4__ {TYPE_1__ prog_array; void* map; } ;
struct trace {TYPE_2__ syscalls; } ;

/* Variables and functions */
 void* trace__find_bpf_map_by_name (struct trace*,char*) ; 

__attribute__((used)) static void trace__set_bpf_map_syscalls(struct trace *trace)
{
	trace->syscalls.map = trace__find_bpf_map_by_name(trace, "syscalls");
	trace->syscalls.prog_array.sys_enter = trace__find_bpf_map_by_name(trace, "syscalls_sys_enter");
	trace->syscalls.prog_array.sys_exit  = trace__find_bpf_map_by_name(trace, "syscalls_sys_exit");
}