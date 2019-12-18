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
 int /*<<< orphan*/  CGROUP_PATH ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ check_ancestor_cgroup_ids (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_and_get_cgroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ join_cgroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ send_packet (char*) ; 
 scalar_t__ setup_cgroup_environment () ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
	int cgfd = -1;
	int err = 0;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s iface prog_id\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (setup_cgroup_environment())
		goto err;

	cgfd = create_and_get_cgroup(CGROUP_PATH);
	if (cgfd < 0)
		goto err;

	if (join_cgroup(CGROUP_PATH))
		goto err;

	if (send_packet(argv[1]))
		goto err;

	if (check_ancestor_cgroup_ids(atoi(argv[2])))
		goto err;

	goto out;
err:
	err = -1;
out:
	close(cgfd);
	cleanup_cgroup_environment();
	printf("[%s]\n", err ? "FAIL" : "PASS");
	return err;
}