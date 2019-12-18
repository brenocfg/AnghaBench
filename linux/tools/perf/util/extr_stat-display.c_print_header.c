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
struct target {char* cpu_list; char* pid; char* tid; scalar_t__ system_wide; } ;
struct perf_stat_config {int run_count; int /*<<< orphan*/  csv_output; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  target__has_task (struct target*) ; 

__attribute__((used)) static void print_header(struct perf_stat_config *config,
			 struct target *_target,
			 int argc, const char **argv)
{
	FILE *output = config->output;
	int i;

	fflush(stdout);

	if (!config->csv_output) {
		fprintf(output, "\n");
		fprintf(output, " Performance counter stats for ");
		if (_target->system_wide)
			fprintf(output, "\'system wide");
		else if (_target->cpu_list)
			fprintf(output, "\'CPU(s) %s", _target->cpu_list);
		else if (!target__has_task(_target)) {
			fprintf(output, "\'%s", argv ? argv[0] : "pipe");
			for (i = 1; argv && (i < argc); i++)
				fprintf(output, " %s", argv[i]);
		} else if (_target->pid)
			fprintf(output, "process id \'%s", _target->pid);
		else
			fprintf(output, "thread id \'%s", _target->tid);

		fprintf(output, "\'");
		if (config->run_count > 1)
			fprintf(output, " (%d runs)", config->run_count);
		fprintf(output, ":\n\n");
	}
}