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
struct seq_file {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* synth_event; int /*<<< orphan*/  match_event; int /*<<< orphan*/  match_event_system; } ;
struct action_data {unsigned int n_params; int /*<<< orphan*/ * params; TYPE_2__ onmatch; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void print_onmatch_spec(struct seq_file *m,
			       struct hist_trigger_data *hist_data,
			       struct action_data *data)
{
	unsigned int i;

	seq_printf(m, ":onmatch(%s.%s).", data->onmatch.match_event_system,
		   data->onmatch.match_event);

	seq_printf(m, "%s(", data->onmatch.synth_event->name);

	for (i = 0; i < data->n_params; i++) {
		if (i)
			seq_puts(m, ",");
		seq_printf(m, "%s", data->params[i]);
	}

	seq_puts(m, ")");
}