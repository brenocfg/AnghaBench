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
struct trace_array {int /*<<< orphan*/  err_log; } ;
struct seq_file {struct trace_array* private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* seq_list_next (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *tracing_err_log_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct trace_array *tr = m->private;

	return seq_list_next(v, &tr->err_log, pos);
}