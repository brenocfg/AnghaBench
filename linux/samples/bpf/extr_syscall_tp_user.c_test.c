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

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int* map_fd ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_map (int) ; 

__attribute__((used)) static int test(char *filename, int num_progs)
{
	int i, fd, map0_fds[num_progs], map1_fds[num_progs];

	for (i = 0; i < num_progs; i++) {
		if (load_bpf_file(filename)) {
			fprintf(stderr, "%s", bpf_log_buf);
			return 1;
		}
		printf("prog #%d: map ids %d %d\n", i, map_fd[0], map_fd[1]);
		map0_fds[i] = map_fd[0];
		map1_fds[i] = map_fd[1];
	}

	/* current load_bpf_file has perf_event_open default pid = -1
	 * and cpu = 0, which permits attached bpf execution on
	 * all cpus for all pid's. bpf program execution ignores
	 * cpu affinity.
	 */
	/* trigger some "open" operations */
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open failed: %s\n", strerror(errno));
		return 1;
	}
	close(fd);

	/* verify the map */
	for (i = 0; i < num_progs; i++) {
		verify_map(map0_fds[i]);
		verify_map(map1_fds[i]);
	}

	return 0;
}