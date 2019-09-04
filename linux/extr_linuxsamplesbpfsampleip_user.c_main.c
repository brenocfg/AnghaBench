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
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int DEFAULT_FREQ ; 
 int DEFAULT_SECS ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 int atoi (char*) ; 
 char* bpf_log_buf ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  int_exit ; 
 scalar_t__ load_bpf_file (char*) ; 
 scalar_t__ load_kallsyms () ; 
 int* malloc (int) ; 
 int /*<<< orphan*/ * map_fd ; 
 int nr_cpus ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_ip_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sampling_end (int*) ; 
 scalar_t__ sampling_start (int*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	char filename[256];
	int *pmu_fd, opt, freq = DEFAULT_FREQ, secs = DEFAULT_SECS;

	/* process arguments */
	while ((opt = getopt(argc, argv, "F:h")) != -1) {
		switch (opt) {
		case 'F':
			freq = atoi(optarg);
			break;
		case 'h':
		default:
			usage();
			return 0;
		}
	}
	if (argc - optind == 1)
		secs = atoi(argv[optind]);
	if (freq == 0 || secs == 0) {
		usage();
		return 1;
	}

	/* initialize kernel symbol translation */
	if (load_kallsyms()) {
		fprintf(stderr, "ERROR: loading /proc/kallsyms\n");
		return 2;
	}

	/* create perf FDs for each CPU */
	nr_cpus = sysconf(_SC_NPROCESSORS_CONF);
	pmu_fd = malloc(nr_cpus * sizeof(int));
	if (pmu_fd == NULL) {
		fprintf(stderr, "ERROR: malloc of pmu_fd\n");
		return 1;
	}

	/* load BPF program */
	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	if (load_bpf_file(filename)) {
		fprintf(stderr, "ERROR: loading BPF program (errno %d):\n",
			errno);
		if (strcmp(bpf_log_buf, "") == 0)
			fprintf(stderr, "Try: ulimit -l unlimited\n");
		else
			fprintf(stderr, "%s", bpf_log_buf);
		return 1;
	}
	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	/* do sampling */
	printf("Sampling at %d Hertz for %d seconds. Ctrl-C also ends.\n",
	       freq, secs);
	if (sampling_start(pmu_fd, freq) != 0)
		return 1;
	sleep(secs);
	sampling_end(pmu_fd);
	free(pmu_fd);

	/* output sample counts */
	print_ip_map(map_fd[0]);

	return 0;
}