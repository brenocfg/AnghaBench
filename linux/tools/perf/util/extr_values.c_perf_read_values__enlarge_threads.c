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
struct perf_read_values {int threads_max; void* value; void* tid; void* pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static int perf_read_values__enlarge_threads(struct perf_read_values *values)
{
	int nthreads_max = values->threads_max * 2;
	void *npid = realloc(values->pid, nthreads_max * sizeof(*values->pid)),
	     *ntid = realloc(values->tid, nthreads_max * sizeof(*values->tid)),
	     *nvalue = realloc(values->value, nthreads_max * sizeof(*values->value));

	if (!npid || !ntid || !nvalue)
		goto out_err;

	values->threads_max = nthreads_max;
	values->pid = npid;
	values->tid = ntid;
	values->value = nvalue;
	return 0;
out_err:
	free(npid);
	free(ntid);
	free(nvalue);
	pr_debug("failed to enlarge read_values threads arrays");
	return -ENOMEM;
}