#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hist_trigger_data {TYPE_2__* attrs; } ;
struct TYPE_3__ {unsigned int n_vars; int /*<<< orphan*/ * expr; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {TYPE_1__ var_defs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_var_defs(struct hist_trigger_data *hist_data)
{
	unsigned int i;

	for (i = 0; i < hist_data->attrs->var_defs.n_vars; i++) {
		kfree(hist_data->attrs->var_defs.name[i]);
		kfree(hist_data->attrs->var_defs.expr[i]);
	}

	hist_data->attrs->var_defs.n_vars = 0;
}