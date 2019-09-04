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
typedef  int /*<<< orphan*/  u16 ;
typedef  long pid_t ;

/* Variables and functions */
 int* ALIGN_PTR_UP (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPAGE_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int /*<<< orphan*/  PTRACE_DETACH ; 
 int /*<<< orphan*/  PTRACE_PEEKDATA ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int /*<<< orphan*/  do_not_expect_pk_fault (char*) ; 
 int /*<<< orphan*/  dprintf1 (char*,int /*<<< orphan*/ ,long,...) ; 
 int /*<<< orphan*/  dprintf2 (char*,int) ; 
 int /*<<< orphan*/  expected_pk_fault (int /*<<< orphan*/ ) ; 
 long fork_lazy_child () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  getpid () ; 
 long kill (long,int /*<<< orphan*/ ) ; 
 int* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pkey_access_deny (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int /*<<< orphan*/  pkey_write_deny (int /*<<< orphan*/ ) ; 
 long ptrace (int /*<<< orphan*/ ,long,void*,void*) ; 
 int read_ptr (int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait (int*) ; 
 long waitpid (long,int*,int /*<<< orphan*/ ) ; 

void test_ptrace_of_child(int *ptr, u16 pkey)
{
	__attribute__((__unused__)) int peek_result;
	pid_t child_pid;
	void *ignored = 0;
	long ret;
	int status;
	/*
	 * This is the "control" for our little expermient.  Make sure
	 * we can always access it when ptracing.
	 */
	int *plain_ptr_unaligned = malloc(HPAGE_SIZE);
	int *plain_ptr = ALIGN_PTR_UP(plain_ptr_unaligned, PAGE_SIZE);

	/*
	 * Fork a child which is an exact copy of this process, of course.
	 * That means we can do all of our tests via ptrace() and then plain
	 * memory access and ensure they work differently.
	 */
	child_pid = fork_lazy_child();
	dprintf1("[%d] child pid: %d\n", getpid(), child_pid);

	ret = ptrace(PTRACE_ATTACH, child_pid, ignored, ignored);
	if (ret)
		perror("attach");
	dprintf1("[%d] attach ret: %ld %d\n", getpid(), ret, __LINE__);
	pkey_assert(ret != -1);
	ret = waitpid(child_pid, &status, WUNTRACED);
	if ((ret != child_pid) || !(WIFSTOPPED(status))) {
		fprintf(stderr, "weird waitpid result %ld stat %x\n",
				ret, status);
		pkey_assert(0);
	}
	dprintf2("waitpid ret: %ld\n", ret);
	dprintf2("waitpid status: %d\n", status);

	pkey_access_deny(pkey);
	pkey_write_deny(pkey);

	/* Write access, untested for now:
	ret = ptrace(PTRACE_POKEDATA, child_pid, peek_at, data);
	pkey_assert(ret != -1);
	dprintf1("poke at %p: %ld\n", peek_at, ret);
	*/

	/*
	 * Try to access the pkey-protected "ptr" via ptrace:
	 */
	ret = ptrace(PTRACE_PEEKDATA, child_pid, ptr, ignored);
	/* expect it to work, without an error: */
	pkey_assert(ret != -1);
	/* Now access from the current task, and expect an exception: */
	peek_result = read_ptr(ptr);
	expected_pk_fault(pkey);

	/*
	 * Try to access the NON-pkey-protected "plain_ptr" via ptrace:
	 */
	ret = ptrace(PTRACE_PEEKDATA, child_pid, plain_ptr, ignored);
	/* expect it to work, without an error: */
	pkey_assert(ret != -1);
	/* Now access from the current task, and expect NO exception: */
	peek_result = read_ptr(plain_ptr);
	do_not_expect_pk_fault("read plain pointer after ptrace");

	ret = ptrace(PTRACE_DETACH, child_pid, ignored, 0);
	pkey_assert(ret != -1);

	ret = kill(child_pid, SIGKILL);
	pkey_assert(ret != -1);

	wait(&status);

	free(plain_ptr_unaligned);
}