#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * output; } ;
struct TYPE_4__ {char* cpu_list; char* pid; char* tid; scalar_t__ system_wide; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  csv_output ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int run_count ; 
 TYPE_3__ stat_config ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_1__ target ; 
 int /*<<< orphan*/  target__has_task (TYPE_1__*) ; 

__attribute__((used)) static void print_header(int argc, const char **argv)
{
	FILE *output = stat_config.output;
	int i;

	fflush(stdout);

	if (!csv_output) {
		fprintf(output, "\n");
		fprintf(output, " Performance counter stats for ");
		if (target.system_wide)
			fprintf(output, "\'system wide");
		else if (target.cpu_list)
			fprintf(output, "\'CPU(s) %s", target.cpu_list);
		else if (!target__has_task(&target)) {
			fprintf(output, "\'%s", argv ? argv[0] : "pipe");
			for (i = 1; argv && (i < argc); i++)
				fprintf(output, " %s", argv[i]);
		} else if (target.pid)
			fprintf(output, "process id \'%s", target.pid);
		else
			fprintf(output, "thread id \'%s", target.tid);

		fprintf(output, "\'");
		if (run_count > 1)
			fprintf(output, " (%d runs)", run_count);
		fprintf(output, ":\n\n");
	}
}