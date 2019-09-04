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
struct agent_info {int cpus; int /*<<< orphan*/  ctl_fd; int /*<<< orphan*/ * rw_ti; int /*<<< orphan*/  pipe_size; int /*<<< orphan*/  use_stdout; } ;

/* Variables and functions */
 scalar_t__ CTL_PATH ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* make_input_path (int) ; 
 char* make_output_path (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rw_ctl_init (char const*) ; 
 int /*<<< orphan*/  rw_thread_init (int,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *agent_info_init(struct agent_info *s)
{
	int cpu;
	const char *in_path = NULL;
	const char *out_path = NULL;

	/* init read/write threads */
	for (cpu = 0; cpu < s->cpus; cpu++) {
		/* set read(input) path per read/write thread */
		in_path = make_input_path(cpu);
		if (in_path == NULL)
			goto error;

		/* set write(output) path per read/write thread*/
		if (!s->use_stdout) {
			out_path = make_output_path(cpu);
			if (out_path == NULL)
				goto error;
		} else
			/* stdout mode */
			pr_debug("stdout mode\n");

		rw_thread_init(cpu, in_path, out_path, s->use_stdout,
						s->pipe_size, s->rw_ti[cpu]);
	}

	/* init controller of read/write threads */
	s->ctl_fd = rw_ctl_init((const char *)CTL_PATH);

	return NULL;

error:
	exit(EXIT_FAILURE);
}