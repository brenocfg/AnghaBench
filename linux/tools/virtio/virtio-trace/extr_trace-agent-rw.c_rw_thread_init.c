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
struct rw_thread_info {int cpu_num; int in_fd; int out_fd; int read_pipe; int write_pipe; unsigned long pipe_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  F_SETPIPE_SZ ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,unsigned long) ; 
 void* open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe2 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

void *rw_thread_init(int cpu, const char *in_path, const char *out_path,
				bool stdout_flag, unsigned long pipe_size,
				struct rw_thread_info *rw_ti)
{
	int data_pipe[2];

	rw_ti->cpu_num = cpu;

	/* set read(input) fd */
	rw_ti->in_fd = open(in_path, O_RDONLY);
	if (rw_ti->in_fd == -1) {
		pr_err("Could not open in_fd (CPU:%d)\n", cpu);
		goto error;
	}

	/* set write(output) fd */
	if (!stdout_flag) {
		/* virtio-serial output mode */
		rw_ti->out_fd = open(out_path, O_WRONLY);
		if (rw_ti->out_fd == -1) {
			pr_err("Could not open out_fd (CPU:%d)\n", cpu);
			goto error;
		}
	} else
		/* stdout mode */
		rw_ti->out_fd = STDOUT_FILENO;

	if (pipe2(data_pipe, O_NONBLOCK) < 0) {
		pr_err("Could not create pipe in rw-thread(%d)\n", cpu);
		goto error;
	}

	/*
	 * Size of pipe is 64kB in default based on fs/pipe.c.
	 * To read/write trace data speedy, pipe size is changed.
	 */
	if (fcntl(*data_pipe, F_SETPIPE_SZ, pipe_size) < 0) {
		pr_err("Could not change pipe size in rw-thread(%d)\n", cpu);
		goto error;
	}

	rw_ti->read_pipe = data_pipe[1];
	rw_ti->write_pipe = data_pipe[0];
	rw_ti->pipe_size = pipe_size;

	return NULL;

error:
	exit(EXIT_FAILURE);
}