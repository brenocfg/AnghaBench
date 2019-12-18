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
struct hist_trigger_data {unsigned int n_field_var_hists; TYPE_1__** field_var_hists; } ;
struct TYPE_2__ {struct TYPE_2__* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void destroy_field_var_hists(struct hist_trigger_data *hist_data)
{
	unsigned int i;

	for (i = 0; i < hist_data->n_field_var_hists; i++) {
		kfree(hist_data->field_var_hists[i]->cmd);
		kfree(hist_data->field_var_hists[i]);
	}
}