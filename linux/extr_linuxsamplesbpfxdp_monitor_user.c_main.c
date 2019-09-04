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
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  bpf_obj_file ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int atoi (int /*<<< orphan*/ ) ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * event_fd ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_bpf_prog_info () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * prog_fd ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stats_poll (int,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	int longindex = 0, opt;
	int ret = EXIT_SUCCESS;
	char bpf_obj_file[256];

	/* Default settings: */
	bool errors_only = true;
	int interval = 2;

	snprintf(bpf_obj_file, sizeof(bpf_obj_file), "%s_kern.o", argv[0]);

	/* Parse commands line args */
	while ((opt = getopt_long(argc, argv, "hDSs:",
				  long_options, &longindex)) != -1) {
		switch (opt) {
		case 'D':
			debug = true;
			break;
		case 'S':
			errors_only = false;
			break;
		case 's':
			interval = atoi(optarg);
			break;
		case 'h':
		default:
			usage(argv);
			return EXIT_FAILURE;
		}
	}

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return EXIT_FAILURE;
	}

	if (load_bpf_file(bpf_obj_file)) {
		printf("ERROR - bpf_log_buf: %s", bpf_log_buf);
		return EXIT_FAILURE;
	}
	if (!prog_fd[0]) {
		printf("ERROR - load_bpf_file: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if (debug) {
		print_bpf_prog_info();
	}

	/* Unload/stop tracepoint event by closing fd's */
	if (errors_only) {
		/* The prog_fd[i] and event_fd[i] depend on the
		 * order the functions was defined in _kern.c
		 */
		close(event_fd[2]); /* tracepoint/xdp/xdp_redirect */
		close(prog_fd[2]);  /* func: trace_xdp_redirect */
		close(event_fd[3]); /* tracepoint/xdp/xdp_redirect_map */
		close(prog_fd[3]);  /* func: trace_xdp_redirect_map */
	}

	stats_poll(interval, errors_only);

	return ret;
}