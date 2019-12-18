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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 char* CGROUP_PATH ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  bpf_map_lookup_elem (int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 scalar_t__ bpf_map_update_elem (int /*<<< orphan*/ ,int*,...) ; 
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_and_get_cgroup (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ getpid () ; 
 scalar_t__ join_cgroup (char*) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/ * map_fd ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ setup_cgroup_environment () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sync () ; 

int main(int argc, char **argv)
{
	pid_t remote_pid, local_pid = getpid();
	int cg2, idx = 0, rc = 0;
	char filename[256];

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	if (setup_cgroup_environment())
		goto err;

	cg2 = create_and_get_cgroup(CGROUP_PATH);

	if (cg2 < 0)
		goto err;

	if (bpf_map_update_elem(map_fd[0], &idx, &cg2, BPF_ANY)) {
		log_err("Adding target cgroup to map");
		goto err;
	}

	if (join_cgroup(CGROUP_PATH))
		goto err;

	/*
	 * The installed helper program catched the sync call, and should
	 * write it to the map.
	 */

	sync();
	bpf_map_lookup_elem(map_fd[1], &idx, &remote_pid);

	if (local_pid != remote_pid) {
		fprintf(stderr,
			"BPF Helper didn't write correct PID to map, but: %d\n",
			remote_pid);
		goto err;
	}

	/* Verify the negative scenario; leave the cgroup */
	if (join_cgroup("/"))
		goto err;

	remote_pid = 0;
	bpf_map_update_elem(map_fd[1], &idx, &remote_pid, BPF_ANY);

	sync();
	bpf_map_lookup_elem(map_fd[1], &idx, &remote_pid);

	if (local_pid == remote_pid) {
		fprintf(stderr, "BPF cgroup negative test did not work\n");
		goto err;
	}

	goto out;
err:
	rc = 1;

out:
	close(cg2);
	cleanup_cgroup_environment();
	return rc;
}