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
struct tracing_map_elt {struct hist_elt_data* private_data; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_field {size_t var_ref_idx; } ;
struct hist_elt_data {int /*<<< orphan*/ * var_ref_vals; } ;

/* Variables and functions */

__attribute__((used)) static u64 hist_field_var_ref(struct hist_field *hist_field,
			      struct tracing_map_elt *elt,
			      struct ring_buffer_event *rbe,
			      void *event)
{
	struct hist_elt_data *elt_data;
	u64 var_val = 0;

	elt_data = elt->private_data;
	var_val = elt_data->var_ref_vals[hist_field->var_ref_idx];

	return var_val;
}