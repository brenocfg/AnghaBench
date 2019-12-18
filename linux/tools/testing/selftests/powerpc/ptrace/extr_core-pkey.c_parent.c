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
struct shared_info {unsigned long amr; unsigned long iamr; unsigned long uamor; int /*<<< orphan*/  child_sync; } ;
typedef  int pid_t ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  NT_PPC_PKEY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PARENT_FAIL_IF (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARENT_SKIP_IF_UNSUPPORTED (int,int /*<<< orphan*/ *) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PROT_READ ; 
 int TEST_FAIL ; 
 int /*<<< orphan*/  WCOREDUMP (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int check_core_file (struct shared_info*,void*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int prod_child (int /*<<< orphan*/ *) ; 
 int ptrace_read_regs (int,int /*<<< orphan*/ ,unsigned long*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 int try_core_file (char*,struct shared_info*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int wait (int*) ; 

__attribute__((used)) static int parent(struct shared_info *info, pid_t pid)
{
	char *filenames, *filename[3];
	int fd, i, ret, status;
	unsigned long regs[3];
	off_t core_size;
	void *core;

	/*
	 * Get the initial values for AMR, IAMR and UAMOR and communicate them
	 * to the child.
	 */
	ret = ptrace_read_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_SKIP_IF_UNSUPPORTED(ret, &info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	info->amr = regs[0];
	info->iamr = regs[1];
	info->uamor = regs[2];

	/* Wake up child so that it can set itself up. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = wait(&status);
	if (ret != pid) {
		printf("Child's exit status not captured\n");
		return TEST_FAIL;
	} else if (!WIFSIGNALED(status) || !WCOREDUMP(status)) {
		printf("Child didn't dump core\n");
		return TEST_FAIL;
	}

	/* Construct array of core file names to try. */

	filename[0] = filenames = malloc(PATH_MAX);
	if (!filenames) {
		perror("Error allocating memory");
		return TEST_FAIL;
	}

	ret = snprintf(filename[0], PATH_MAX, "core-pkey.%d", pid);
	if (ret < 0 || ret >= PATH_MAX) {
		ret = TEST_FAIL;
		goto out;
	}

	filename[1] = filename[0] + ret + 1;
	ret = snprintf(filename[1], PATH_MAX - ret - 1, "core.%d", pid);
	if (ret < 0 || ret >= PATH_MAX - ret - 1) {
		ret = TEST_FAIL;
		goto out;
	}
	filename[2] = "core";

	for (i = 0; i < 3; i++) {
		core_size = try_core_file(filename[i], info, pid);
		if (core_size != TEST_FAIL)
			break;
	}

	if (i == 3) {
		printf("Couldn't find core file\n");
		ret = TEST_FAIL;
		goto out;
	}

	fd = open(filename[i], O_RDONLY);
	if (fd == -1) {
		perror("Error opening core file");
		ret = TEST_FAIL;
		goto out;
	}

	core = mmap(NULL, core_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (core == (void *) -1) {
		perror("Error mmaping core file");
		ret = TEST_FAIL;
		goto out;
	}

	ret = check_core_file(info, core, core_size);

	munmap(core, core_size);
	close(fd);
	unlink(filename[i]);

 out:
	free(filenames);

	return ret;
}