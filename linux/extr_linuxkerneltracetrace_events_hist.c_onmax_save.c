#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct tracing_map_elt {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct TYPE_6__ {unsigned int max_var_ref_idx; TYPE_2__* max_var; } ;
struct action_data {TYPE_3__ onmax; } ;
struct TYPE_4__ {unsigned int idx; } ;
struct TYPE_5__ {TYPE_1__ var; } ;

/* Variables and functions */
 scalar_t__ tracing_map_read_var (struct tracing_map_elt*,unsigned int) ; 
 int /*<<< orphan*/  tracing_map_set_var (struct tracing_map_elt*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  update_max_vars (struct hist_trigger_data*,struct tracing_map_elt*,struct ring_buffer_event*,void*) ; 

__attribute__((used)) static void onmax_save(struct hist_trigger_data *hist_data,
		       struct tracing_map_elt *elt, void *rec,
		       struct ring_buffer_event *rbe,
		       struct action_data *data, u64 *var_ref_vals)
{
	unsigned int max_idx = data->onmax.max_var->var.idx;
	unsigned int max_var_ref_idx = data->onmax.max_var_ref_idx;

	u64 var_val, max_val;

	var_val = var_ref_vals[max_var_ref_idx];
	max_val = tracing_map_read_var(elt, max_idx);

	if (var_val <= max_val)
		return;

	tracing_map_set_var(elt, max_idx, var_val);

	update_max_vars(hist_data, elt, rbe, rec);
}