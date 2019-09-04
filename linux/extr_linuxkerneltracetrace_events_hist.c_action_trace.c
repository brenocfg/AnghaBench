#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct synth_event {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  var_ref_idx; struct synth_event* synth_event; } ;
struct action_data {TYPE_1__ onmatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_synth (struct synth_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void action_trace(struct hist_trigger_data *hist_data,
			 struct tracing_map_elt *elt, void *rec,
			 struct ring_buffer_event *rbe,
			 struct action_data *data, u64 *var_ref_vals)
{
	struct synth_event *event = data->onmatch.synth_event;

	trace_synth(event, var_ref_vals, data->onmatch.var_ref_idx);
}