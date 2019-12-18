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
struct sockmap_options {int verbose; int data_test; int iov_count; int iov_length; int rate; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int BASE ; 
 int BASE_SENDPAGE ; 
 char* BPF_SOCKMAP_FILENAME ; 
 int /*<<< orphan*/  O_DIRECTORY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PING_PONG ; 
 int SENDMSG ; 
 int SENDPAGE ; 
 int /*<<< orphan*/  SIGINT ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int populate_progs (char*) ; 
 int run_options (struct sockmap_options*,int,int) ; 
 int running ; 
 int /*<<< orphan*/  running_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int test_suite (int) ; 
 void* txmsg_apply ; 
 void* txmsg_cork ; 
 void* txmsg_end ; 
 void* txmsg_end_push ; 
 void* txmsg_pop ; 
 void* txmsg_start ; 
 void* txmsg_start_pop ; 
 void* txmsg_start_push ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char **argv)
{
	int iov_count = 1, length = 1024, rate = 1;
	struct sockmap_options options = {0};
	int opt, longindex, err, cg_fd = 0;
	char *bpf_file = BPF_SOCKMAP_FILENAME;
	int test = PING_PONG;

	if (argc < 2)
		return test_suite(-1);

	while ((opt = getopt_long(argc, argv, ":dhvc:r:i:l:t:p:q:",
				  long_options, &longindex)) != -1) {
		switch (opt) {
		case 's':
			txmsg_start = atoi(optarg);
			break;
		case 'e':
			txmsg_end = atoi(optarg);
			break;
		case 'p':
			txmsg_start_push = atoi(optarg);
			break;
		case 'q':
			txmsg_end_push = atoi(optarg);
			break;
		case 'w':
			txmsg_start_pop = atoi(optarg);
			break;
		case 'x':
			txmsg_pop = atoi(optarg);
			break;
		case 'a':
			txmsg_apply = atoi(optarg);
			break;
		case 'k':
			txmsg_cork = atoi(optarg);
			break;
		case 'c':
			cg_fd = open(optarg, O_DIRECTORY, O_RDONLY);
			if (cg_fd < 0) {
				fprintf(stderr,
					"ERROR: (%i) open cg path failed: %s\n",
					cg_fd, optarg);
				return cg_fd;
			}
			break;
		case 'r':
			rate = atoi(optarg);
			break;
		case 'v':
			options.verbose = 1;
			break;
		case 'i':
			iov_count = atoi(optarg);
			break;
		case 'l':
			length = atoi(optarg);
			break;
		case 'd':
			options.data_test = true;
			break;
		case 't':
			if (strcmp(optarg, "ping") == 0) {
				test = PING_PONG;
			} else if (strcmp(optarg, "sendmsg") == 0) {
				test = SENDMSG;
			} else if (strcmp(optarg, "base") == 0) {
				test = BASE;
			} else if (strcmp(optarg, "base_sendpage") == 0) {
				test = BASE_SENDPAGE;
			} else if (strcmp(optarg, "sendpage") == 0) {
				test = SENDPAGE;
			} else {
				usage(argv);
				return -1;
			}
			break;
		case 0:
			break;
		case 'h':
		default:
			usage(argv);
			return -1;
		}
	}

	if (argc <= 3 && cg_fd)
		return test_suite(cg_fd);

	if (!cg_fd) {
		fprintf(stderr, "%s requires cgroup option: --cgroup <path>\n",
			argv[0]);
		return -1;
	}

	err = populate_progs(bpf_file);
	if (err) {
		fprintf(stderr, "populate program: (%s) %s\n",
			bpf_file, strerror(errno));
		return 1;
	}
	running = 1;

	/* catch SIGINT */
	signal(SIGINT, running_handler);

	options.iov_count = iov_count;
	options.iov_length = length;
	options.rate = rate;

	err = run_options(&options, cg_fd, test);
	close(cg_fd);
	return err;
}