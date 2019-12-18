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
struct seq_file {int dummy; } ;
struct event_trigger_ops {int dummy; } ;
struct event_trigger_data {int /*<<< orphan*/  filter_str; scalar_t__ count; } ;

/* Variables and functions */
 int event_trigger_print (char*,struct seq_file*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
traceon_trigger_print(struct seq_file *m, struct event_trigger_ops *ops,
		      struct event_trigger_data *data)
{
	return event_trigger_print("traceon", m, (void *)data->count,
				   data->filter_str);
}