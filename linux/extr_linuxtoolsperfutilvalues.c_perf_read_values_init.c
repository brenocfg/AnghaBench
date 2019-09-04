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
struct perf_read_values {int threads_max; int counters_max; void* value; void* tid; void* pid; void* countername; void* counterrawid; scalar_t__ counters; scalar_t__ threads; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 void* zalloc (int) ; 
 int /*<<< orphan*/  zfree (void**) ; 

int perf_read_values_init(struct perf_read_values *values)
{
	values->threads_max = 16;
	values->pid = malloc(values->threads_max * sizeof(*values->pid));
	values->tid = malloc(values->threads_max * sizeof(*values->tid));
	values->value = zalloc(values->threads_max * sizeof(*values->value));
	if (!values->pid || !values->tid || !values->value) {
		pr_debug("failed to allocate read_values threads arrays");
		goto out_free_pid;
	}
	values->threads = 0;

	values->counters_max = 16;
	values->counterrawid = malloc(values->counters_max
				      * sizeof(*values->counterrawid));
	values->countername = malloc(values->counters_max
				     * sizeof(*values->countername));
	if (!values->counterrawid || !values->countername) {
		pr_debug("failed to allocate read_values counters arrays");
		goto out_free_counter;
	}
	values->counters = 0;

	return 0;

out_free_counter:
	zfree(&values->counterrawid);
	zfree(&values->countername);
out_free_pid:
	zfree(&values->pid);
	zfree(&values->tid);
	zfree(&values->value);
	return -ENOMEM;
}