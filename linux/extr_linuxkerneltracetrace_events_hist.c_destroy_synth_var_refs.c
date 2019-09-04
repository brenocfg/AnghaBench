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
struct hist_trigger_data {unsigned int n_synth_var_refs; int /*<<< orphan*/ * synth_var_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_hist_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_synth_var_refs(struct hist_trigger_data *hist_data)
{
	unsigned int i;

	for (i = 0; i < hist_data->n_synth_var_refs; i++)
		destroy_hist_field(hist_data->synth_var_refs[i], 0);
}