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
struct trace_array {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int /*<<< orphan*/  snapshot_fops ; 
 int /*<<< orphan*/  snapshot_raw_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long) ; 
 int /*<<< orphan*/  trace_create_cpu_file (char*,int,struct dentry*,struct trace_array*,long,int /*<<< orphan*/ *) ; 
 struct dentry* tracefs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  tracing_buffers_fops ; 
 struct dentry* tracing_dentry_percpu (struct trace_array*,long) ; 
 int /*<<< orphan*/  tracing_entries_fops ; 
 int /*<<< orphan*/  tracing_fops ; 
 int /*<<< orphan*/  tracing_pipe_fops ; 
 int /*<<< orphan*/  tracing_stats_fops ; 

__attribute__((used)) static void
tracing_init_tracefs_percpu(struct trace_array *tr, long cpu)
{
	struct dentry *d_percpu = tracing_dentry_percpu(tr, cpu);
	struct dentry *d_cpu;
	char cpu_dir[30]; /* 30 characters should be more than enough */

	if (!d_percpu)
		return;

	snprintf(cpu_dir, 30, "cpu%ld", cpu);
	d_cpu = tracefs_create_dir(cpu_dir, d_percpu);
	if (!d_cpu) {
		pr_warn("Could not create tracefs '%s' entry\n", cpu_dir);
		return;
	}

	/* per cpu trace_pipe */
	trace_create_cpu_file("trace_pipe", 0444, d_cpu,
				tr, cpu, &tracing_pipe_fops);

	/* per cpu trace */
	trace_create_cpu_file("trace", 0644, d_cpu,
				tr, cpu, &tracing_fops);

	trace_create_cpu_file("trace_pipe_raw", 0444, d_cpu,
				tr, cpu, &tracing_buffers_fops);

	trace_create_cpu_file("stats", 0444, d_cpu,
				tr, cpu, &tracing_stats_fops);

	trace_create_cpu_file("buffer_size_kb", 0444, d_cpu,
				tr, cpu, &tracing_entries_fops);

#ifdef CONFIG_TRACER_SNAPSHOT
	trace_create_cpu_file("snapshot", 0644, d_cpu,
				tr, cpu, &snapshot_fops);

	trace_create_cpu_file("snapshot_raw", 0444, d_cpu,
				tr, cpu, &snapshot_raw_fops);
#endif
}