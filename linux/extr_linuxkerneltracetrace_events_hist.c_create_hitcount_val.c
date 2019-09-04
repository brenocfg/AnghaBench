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
struct hist_trigger_data {scalar_t__ n_vals; int /*<<< orphan*/  n_fields; int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HIST_FIELD_FL_HITCOUNT ; 
 size_t HITCOUNT_IDX ; 
 scalar_t__ TRACING_MAP_VALS_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  create_hist_field (struct hist_trigger_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_hitcount_val(struct hist_trigger_data *hist_data)
{
	hist_data->fields[HITCOUNT_IDX] =
		create_hist_field(hist_data, NULL, HIST_FIELD_FL_HITCOUNT, NULL);
	if (!hist_data->fields[HITCOUNT_IDX])
		return -ENOMEM;

	hist_data->n_vals++;
	hist_data->n_fields++;

	if (WARN_ON(hist_data->n_vals > TRACING_MAP_VALS_MAX))
		return -EINVAL;

	return 0;
}