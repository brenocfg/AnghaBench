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
typedef  int /*<<< orphan*/  bpf_file ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  dump_all_counts () ; 
 int /*<<< orphan*/  dump_exit ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/  long_options ; 
 char* optarg ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (unsigned long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
	unsigned long delay = 5;
	int longindex = 0;
	int opt;
	char bpf_file[256];

	/* Create the eBPF kernel code path name.
	 * This follows the pattern of all of the other bpf samples
	 */
	snprintf(bpf_file, sizeof(bpf_file), "%s_kern.o", argv[0]);

	/* Do one final dump when exiting */
	signal(SIGINT, dump_exit);
	signal(SIGTERM, dump_exit);

	while ((opt = getopt_long(argc, argv, "hd:rSw",
				  long_options, &longindex)) != -1) {
		switch (opt) {
		case 'd':
			delay = strtoul(optarg, NULL, 0);
			if (delay == ULONG_MAX || delay < 0 ||
			    delay > 1000000) {
				fprintf(stderr, "ERROR: invalid delay : %s\n",
					optarg);
				usage(argv[0]);
				return 1;
			}
			break;
		default:
		case 'h':
			usage(argv[0]);
			return 1;
		}
	}

	if (load_bpf_file(bpf_file)) {
		fprintf(stderr, "ERROR: failed to load eBPF from file : %s\n",
			bpf_file);
		return 1;
	}

	while (1) {
		sleep(delay);
		dump_all_counts();
	}

	return 0;
}