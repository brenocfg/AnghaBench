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
struct TYPE_2__ {struct action_data* fn_name; struct action_data* var_str; int /*<<< orphan*/  var; int /*<<< orphan*/  max_var; } ;
struct action_data {unsigned int n_params; struct action_data** params; TYPE_1__ onmax; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_hist_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct action_data*) ; 

__attribute__((used)) static void onmax_destroy(struct action_data *data)
{
	unsigned int i;

	destroy_hist_field(data->onmax.max_var, 0);
	destroy_hist_field(data->onmax.var, 0);

	kfree(data->onmax.var_str);
	kfree(data->onmax.fn_name);

	for (i = 0; i < data->n_params; i++)
		kfree(data->params[i]);

	kfree(data);
}