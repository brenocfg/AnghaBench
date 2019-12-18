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
struct seq_file {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event; int /*<<< orphan*/  event_system; } ;
struct action_data {int /*<<< orphan*/  action_name; TYPE_1__ match_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_action_spec (struct seq_file*,struct hist_trigger_data*,struct action_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void print_onmatch_spec(struct seq_file *m,
			       struct hist_trigger_data *hist_data,
			       struct action_data *data)
{
	seq_printf(m, ":onmatch(%s.%s).", data->match_data.event_system,
		   data->match_data.event);

	seq_printf(m, "%s(", data->action_name);

	print_action_spec(m, hist_data, data);

	seq_puts(m, ")");
}