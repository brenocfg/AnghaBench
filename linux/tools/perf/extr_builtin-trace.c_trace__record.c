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
struct trace {int trace_pgfaults; scalar_t__ trace_syscalls; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
 int ENOMEM ; 
 int TRACE_PFMAJ ; 
 int TRACE_PFMIN ; 
 char** calloc (unsigned int,int) ; 
 int cmd_record (unsigned int,char const**) ; 
 int /*<<< orphan*/  free (char const**) ; 
 scalar_t__ is_valid_tracepoint (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int trace__record(struct trace *trace, int argc, const char **argv)
{
	unsigned int rec_argc, i, j;
	const char **rec_argv;
	const char * const record_args[] = {
		"record",
		"-R",
		"-m", "1024",
		"-c", "1",
	};

	const char * const sc_args[] = { "-e", };
	unsigned int sc_args_nr = ARRAY_SIZE(sc_args);
	const char * const majpf_args[] = { "-e", "major-faults" };
	unsigned int majpf_args_nr = ARRAY_SIZE(majpf_args);
	const char * const minpf_args[] = { "-e", "minor-faults" };
	unsigned int minpf_args_nr = ARRAY_SIZE(minpf_args);

	/* +1 is for the event string below */
	rec_argc = ARRAY_SIZE(record_args) + sc_args_nr + 1 +
		majpf_args_nr + minpf_args_nr + argc;
	rec_argv = calloc(rec_argc + 1, sizeof(char *));

	if (rec_argv == NULL)
		return -ENOMEM;

	j = 0;
	for (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[j++] = record_args[i];

	if (trace->trace_syscalls) {
		for (i = 0; i < sc_args_nr; i++)
			rec_argv[j++] = sc_args[i];

		/* event string may be different for older kernels - e.g., RHEL6 */
		if (is_valid_tracepoint("raw_syscalls:sys_enter"))
			rec_argv[j++] = "raw_syscalls:sys_enter,raw_syscalls:sys_exit";
		else if (is_valid_tracepoint("syscalls:sys_enter"))
			rec_argv[j++] = "syscalls:sys_enter,syscalls:sys_exit";
		else {
			pr_err("Neither raw_syscalls nor syscalls events exist.\n");
			free(rec_argv);
			return -1;
		}
	}

	if (trace->trace_pgfaults & TRACE_PFMAJ)
		for (i = 0; i < majpf_args_nr; i++)
			rec_argv[j++] = majpf_args[i];

	if (trace->trace_pgfaults & TRACE_PFMIN)
		for (i = 0; i < minpf_args_nr; i++)
			rec_argv[j++] = minpf_args[i];

	for (i = 0; i < (unsigned int)argc; i++)
		rec_argv[j++] = argv[i];

	return cmd_record(j, rec_argv);
}