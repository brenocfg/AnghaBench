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
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_and_get_cgroup (int /*<<< orphan*/ ) ; 
 scalar_t__ join_cgroup (int /*<<< orphan*/ ) ; 
 scalar_t__ run_tests (int) ; 
 scalar_t__ setup_cgroup_environment () ; 

int main(int argc, char **argv)
{
	int cgfd = -1;
	int err = 0;

	if (setup_cgroup_environment())
		goto err;

	cgfd = create_and_get_cgroup(CG_PATH);
	if (cgfd < 0)
		goto err;

	if (join_cgroup(CG_PATH))
		goto err;

	if (run_tests(cgfd))
		goto err;

	goto out;
err:
	err = -1;
out:
	close(cgfd);
	cleanup_cgroup_environment();
	return err;
}