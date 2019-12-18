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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 char* buff ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit_tracelog ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_tracefs_pipe (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pipe_fd ; 

int do_tracelog(int argc, char **argv)
{
	const struct sigaction act = {
		.sa_handler = exit_tracelog
	};
	char trace_pipe[PATH_MAX];
	size_t buff_len = 0;

	if (json_output)
		jsonw_start_array(json_wtr);

	if (!get_tracefs_pipe(trace_pipe))
		return -1;

	trace_pipe_fd = fopen(trace_pipe, "r");
	if (!trace_pipe_fd) {
		p_err("could not open trace pipe: %s", strerror(errno));
		return -1;
	}

	sigaction(SIGHUP, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	while (1) {
		ssize_t ret;

		ret = getline(&buff, &buff_len, trace_pipe_fd);
		if (ret <= 0) {
			p_err("failed to read content from trace pipe: %s",
			      strerror(errno));
			break;
		}
		if (json_output)
			jsonw_string(json_wtr, buff);
		else
			printf("%s", buff);
	}

	fclose(trace_pipe_fd);
	free(buff);
	return -1;
}