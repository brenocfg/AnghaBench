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
typedef  int __u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BPF_CGROUP_INET_EGRESS ; 
 int /*<<< orphan*/  BPF_F_ALLOW_MULTI ; 
 int /*<<< orphan*/  PING_CMD ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bpf_prog_attach (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_prog_get_fd_by_id (int) ; 
 scalar_t__ bpf_prog_query (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_and_get_cgroup (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ join_cgroup (char*) ; 
 int /*<<< orphan*/  log_err (char*,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int prog_load_cnt (int,int) ; 
 scalar_t__ setup_cgroup_environment () ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_autodetach(void)
{
	__u32 prog_cnt = 4, attach_flags;
	int allow_prog[2] = {0};
	__u32 prog_ids[2] = {0};
	int cg = 0, i, rc = -1;
	void *ptr = NULL;
	int attempts;

	for (i = 0; i < ARRAY_SIZE(allow_prog); i++) {
		allow_prog[i] = prog_load_cnt(1, 1 << i);
		if (!allow_prog[i])
			goto err;
	}

	if (setup_cgroup_environment())
		goto err;

	/* create a cgroup, attach two programs and remember their ids */
	cg = create_and_get_cgroup("/cg_autodetach");
	if (cg < 0)
		goto err;

	if (join_cgroup("/cg_autodetach"))
		goto err;

	for (i = 0; i < ARRAY_SIZE(allow_prog); i++) {
		if (bpf_prog_attach(allow_prog[i], cg, BPF_CGROUP_INET_EGRESS,
				    BPF_F_ALLOW_MULTI)) {
			log_err("Attaching prog[%d] to cg:egress", i);
			goto err;
		}
	}

	/* make sure that programs are attached and run some traffic */
	assert(bpf_prog_query(cg, BPF_CGROUP_INET_EGRESS, 0, &attach_flags,
			      prog_ids, &prog_cnt) == 0);
	assert(system(PING_CMD) == 0);

	/* allocate some memory (4Mb) to pin the original cgroup */
	ptr = malloc(4 * (1 << 20));
	if (!ptr)
		goto err;

	/* close programs and cgroup fd */
	for (i = 0; i < ARRAY_SIZE(allow_prog); i++) {
		close(allow_prog[i]);
		allow_prog[i] = 0;
	}

	close(cg);
	cg = 0;

	/* leave the cgroup and remove it. don't detach programs */
	cleanup_cgroup_environment();

	/* wait for the asynchronous auto-detachment.
	 * wait for no more than 5 sec and give up.
	 */
	for (i = 0; i < ARRAY_SIZE(prog_ids); i++) {
		for (attempts = 5; attempts >= 0; attempts--) {
			int fd = bpf_prog_get_fd_by_id(prog_ids[i]);

			if (fd < 0)
				break;

			/* don't leave the fd open */
			close(fd);

			if (!attempts)
				goto err;

			sleep(1);
		}
	}

	rc = 0;
err:
	for (i = 0; i < ARRAY_SIZE(allow_prog); i++)
		if (allow_prog[i] > 0)
			close(allow_prog[i]);
	if (cg)
		close(cg);
	free(ptr);
	cleanup_cgroup_environment();
	if (!rc)
		printf("#autodetach:PASS\n");
	else
		printf("#autodetach:FAIL\n");
	return rc;
}