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
typedef  void tracer ;
struct trace_array {int dummy; } ;
struct seq_file {struct trace_array* private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* get_tracer_for_array (struct trace_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 void* t_next (struct seq_file*,void*,scalar_t__*) ; 
 int /*<<< orphan*/  trace_types ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static void *t_start(struct seq_file *m, loff_t *pos)
{
	struct trace_array *tr = m->private;
	struct tracer *t;
	loff_t l = 0;

	mutex_lock(&trace_types_lock);

	t = get_tracer_for_array(tr, trace_types);
	for (; t && l < *pos; t = t_next(m, t, &l))
			;

	return t;
}