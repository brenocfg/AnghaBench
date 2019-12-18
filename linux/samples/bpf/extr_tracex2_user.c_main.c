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
struct rlimit {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 char* bpf_log_buf ; 
 scalar_t__ bpf_map_get_next_key (int /*<<< orphan*/ ,long*,long*) ; 
 int /*<<< orphan*/  bpf_map_lookup_elem (int /*<<< orphan*/ ,long*,long*) ; 
 int /*<<< orphan*/  int_exit ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/ * map_fd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  print_hist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int main(int ac, char **argv)
{
	struct rlimit r = {1024*1024, RLIM_INFINITY};
	char filename[256];
	long key, next_key, value;
	FILE *f;
	int i;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	/* start 'ping' in the background to have some kfree_skb events */
	f = popen("ping -4 -c5 localhost", "r");
	(void) f;

	/* start 'dd' in the background to have plenty of 'write' syscalls */
	f = popen("dd if=/dev/zero of=/dev/null count=5000000", "r");
	(void) f;

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	for (i = 0; i < 5; i++) {
		key = 0;
		while (bpf_map_get_next_key(map_fd[0], &key, &next_key) == 0) {
			bpf_map_lookup_elem(map_fd[0], &next_key, &value);
			printf("location 0x%lx count %ld\n", next_key, value);
			key = next_key;
		}
		if (key)
			printf("\n");
		sleep(1);
	}
	print_hist(map_fd[1]);

	return 0;
}