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
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
struct trace_array {TYPE_1__ trace_buffer; } ;
struct seq_file {struct trace_array* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ring_buffer_time_stamp_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static int tracing_time_stamp_mode_show(struct seq_file *m, void *v)
{
	struct trace_array *tr = m->private;

	mutex_lock(&trace_types_lock);

	if (ring_buffer_time_stamp_abs(tr->trace_buffer.buffer))
		seq_puts(m, "delta [absolute]\n");
	else
		seq_puts(m, "[delta] absolute\n");

	mutex_unlock(&trace_types_lock);

	return 0;
}