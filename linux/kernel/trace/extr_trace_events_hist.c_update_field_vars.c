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
struct tracing_map_elt {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_trigger_data {int /*<<< orphan*/  n_field_vars; int /*<<< orphan*/  field_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  __update_field_vars (struct tracing_map_elt*,struct ring_buffer_event*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_field_vars(struct hist_trigger_data *hist_data,
			      struct tracing_map_elt *elt,
			      struct ring_buffer_event *rbe,
			      void *rec)
{
	__update_field_vars(elt, rbe, rec, hist_data->field_vars,
			    hist_data->n_field_vars, 0);
}