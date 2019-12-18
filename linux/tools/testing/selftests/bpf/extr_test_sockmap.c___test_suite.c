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
 int /*<<< orphan*/  CG_PATH ; 
 int EINVAL ; 
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_and_get_cgroup (int /*<<< orphan*/ ) ; 
 int failed ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ join_cgroup (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int passed ; 
 int populate_progs (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ setup_cgroup_environment () ; 
 int /*<<< orphan*/  stderr ; 
 int test_mixed (int) ; 
 int test_start_end (int) ; 
 int test_txmsg (int) ; 
 scalar_t__ txmsg_end ; 
 scalar_t__ txmsg_end_push ; 
 scalar_t__ txmsg_start ; 
 scalar_t__ txmsg_start_push ; 

__attribute__((used)) static int __test_suite(int cg_fd, char *bpf_file)
{
	int err, cleanup = cg_fd;

	err = populate_progs(bpf_file);
	if (err < 0) {
		fprintf(stderr, "ERROR: (%i) load bpf failed\n", err);
		return err;
	}

	if (cg_fd < 0) {
		if (setup_cgroup_environment()) {
			fprintf(stderr, "ERROR: cgroup env failed\n");
			return -EINVAL;
		}

		cg_fd = create_and_get_cgroup(CG_PATH);
		if (cg_fd < 0) {
			fprintf(stderr,
				"ERROR: (%i) open cg path failed: %s\n",
				cg_fd, optarg);
			return cg_fd;
		}

		if (join_cgroup(CG_PATH)) {
			fprintf(stderr, "ERROR: failed to join cgroup\n");
			return -EINVAL;
		}
	}

	/* Tests basic commands and APIs with range of iov values */
	txmsg_start = txmsg_end = txmsg_start_push = txmsg_end_push = 0;
	err = test_txmsg(cg_fd);
	if (err)
		goto out;

	/* Tests interesting combinations of APIs used together */
	err = test_mixed(cg_fd);
	if (err)
		goto out;

	/* Tests pull_data API using start/end API */
	err = test_start_end(cg_fd);
	if (err)
		goto out;

out:
	printf("Summary: %i PASSED %i FAILED\n", passed, failed);
	if (cleanup < 0) {
		cleanup_cgroup_environment();
		close(cg_fd);
	}
	return err;
}