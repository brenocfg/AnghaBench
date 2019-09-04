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
struct perf_tool {int /*<<< orphan*/ * feature; int /*<<< orphan*/ * time_conv; int /*<<< orphan*/ * stat_round; int /*<<< orphan*/ * stat; int /*<<< orphan*/ * stat_config; int /*<<< orphan*/ * cpu_map; int /*<<< orphan*/ * thread_map; int /*<<< orphan*/ * auxtrace_error; int /*<<< orphan*/ * auxtrace; int /*<<< orphan*/ * auxtrace_info; int /*<<< orphan*/ * id_index; int /*<<< orphan*/ * finished_round; scalar_t__ ordered_events; int /*<<< orphan*/ * build_id; int /*<<< orphan*/ * tracing_data; int /*<<< orphan*/ * event_update; int /*<<< orphan*/ * attr; int /*<<< orphan*/ * unthrottle; int /*<<< orphan*/ * throttle; int /*<<< orphan*/ * read; int /*<<< orphan*/ * context_switch; int /*<<< orphan*/ * itrace_start; int /*<<< orphan*/ * aux; int /*<<< orphan*/ * lost_samples; int /*<<< orphan*/ * lost; int /*<<< orphan*/ * exit; int /*<<< orphan*/ * fork; int /*<<< orphan*/ * namespaces; int /*<<< orphan*/ * comm; int /*<<< orphan*/ * mmap2; int /*<<< orphan*/ * mmap; int /*<<< orphan*/ * sample; } ;

/* Variables and functions */
 int /*<<< orphan*/ * perf_event__process_aux ; 
 int /*<<< orphan*/ * perf_event__process_itrace_start ; 
 int /*<<< orphan*/ * perf_event__process_lost ; 
 int /*<<< orphan*/ * perf_event__process_lost_samples ; 
 int /*<<< orphan*/ * perf_event__process_switch ; 
 int /*<<< orphan*/ * process_event_auxtrace_stub ; 
 int /*<<< orphan*/ * process_event_cpu_map_stub ; 
 void* process_event_op2_stub ; 
 void* process_event_sample_stub ; 
 int /*<<< orphan*/ * process_event_stat_config_stub ; 
 void* process_event_stub ; 
 int /*<<< orphan*/ * process_event_synth_attr_stub ; 
 int /*<<< orphan*/ * process_event_synth_event_update_stub ; 
 int /*<<< orphan*/ * process_event_synth_tracing_data_stub ; 
 int /*<<< orphan*/ * process_event_thread_map_stub ; 
 int /*<<< orphan*/ * process_finished_round ; 
 int /*<<< orphan*/ * process_finished_round_stub ; 
 int /*<<< orphan*/ * process_stat_round_stub ; 
 int /*<<< orphan*/ * process_stat_stub ; 

void perf_tool__fill_defaults(struct perf_tool *tool)
{
	if (tool->sample == NULL)
		tool->sample = process_event_sample_stub;
	if (tool->mmap == NULL)
		tool->mmap = process_event_stub;
	if (tool->mmap2 == NULL)
		tool->mmap2 = process_event_stub;
	if (tool->comm == NULL)
		tool->comm = process_event_stub;
	if (tool->namespaces == NULL)
		tool->namespaces = process_event_stub;
	if (tool->fork == NULL)
		tool->fork = process_event_stub;
	if (tool->exit == NULL)
		tool->exit = process_event_stub;
	if (tool->lost == NULL)
		tool->lost = perf_event__process_lost;
	if (tool->lost_samples == NULL)
		tool->lost_samples = perf_event__process_lost_samples;
	if (tool->aux == NULL)
		tool->aux = perf_event__process_aux;
	if (tool->itrace_start == NULL)
		tool->itrace_start = perf_event__process_itrace_start;
	if (tool->context_switch == NULL)
		tool->context_switch = perf_event__process_switch;
	if (tool->read == NULL)
		tool->read = process_event_sample_stub;
	if (tool->throttle == NULL)
		tool->throttle = process_event_stub;
	if (tool->unthrottle == NULL)
		tool->unthrottle = process_event_stub;
	if (tool->attr == NULL)
		tool->attr = process_event_synth_attr_stub;
	if (tool->event_update == NULL)
		tool->event_update = process_event_synth_event_update_stub;
	if (tool->tracing_data == NULL)
		tool->tracing_data = process_event_synth_tracing_data_stub;
	if (tool->build_id == NULL)
		tool->build_id = process_event_op2_stub;
	if (tool->finished_round == NULL) {
		if (tool->ordered_events)
			tool->finished_round = process_finished_round;
		else
			tool->finished_round = process_finished_round_stub;
	}
	if (tool->id_index == NULL)
		tool->id_index = process_event_op2_stub;
	if (tool->auxtrace_info == NULL)
		tool->auxtrace_info = process_event_op2_stub;
	if (tool->auxtrace == NULL)
		tool->auxtrace = process_event_auxtrace_stub;
	if (tool->auxtrace_error == NULL)
		tool->auxtrace_error = process_event_op2_stub;
	if (tool->thread_map == NULL)
		tool->thread_map = process_event_thread_map_stub;
	if (tool->cpu_map == NULL)
		tool->cpu_map = process_event_cpu_map_stub;
	if (tool->stat_config == NULL)
		tool->stat_config = process_event_stat_config_stub;
	if (tool->stat == NULL)
		tool->stat = process_stat_stub;
	if (tool->stat_round == NULL)
		tool->stat_round = process_stat_round_stub;
	if (tool->time_conv == NULL)
		tool->time_conv = process_event_op2_stub;
	if (tool->feature == NULL)
		tool->feature = process_event_op2_stub;
}