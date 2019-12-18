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
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_trigger_data {int /*<<< orphan*/  n_field_var_str; int /*<<< orphan*/  n_save_vars; int /*<<< orphan*/  save_vars; } ;
struct action_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __update_field_vars (struct tracing_map_elt*,struct ring_buffer_event*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void save_track_data_vars(struct hist_trigger_data *hist_data,
				 struct tracing_map_elt *elt, void *rec,
				 struct ring_buffer_event *rbe, void *key,
				 struct action_data *data, u64 *var_ref_vals)
{
	__update_field_vars(elt, rbe, rec, hist_data->save_vars,
			    hist_data->n_save_vars, hist_data->n_field_var_str);
}