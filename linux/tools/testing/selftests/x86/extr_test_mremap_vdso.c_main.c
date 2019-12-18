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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYSINFO_EHDR ; 
 unsigned long ENOENT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  SYS_exit ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int errno ; 
 int fork () ; 
 unsigned long getauxval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int) ; 
 int try_to_remap (void*,unsigned long) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv, char **envp)
{
	pid_t child;

	child = fork();
	if (child == -1) {
		printf("[WARN]\tfailed to fork (%d): %m\n", errno);
		return 1;
	}

	if (child == 0) {
		unsigned long vdso_size = PAGE_SIZE;
		unsigned long auxval;
		int ret = -1;

		auxval = getauxval(AT_SYSINFO_EHDR);
		printf("\tAT_SYSINFO_EHDR is %#lx\n", auxval);
		if (!auxval || auxval == -ENOENT) {
			printf("[WARN]\tgetauxval failed\n");
			return 0;
		}

		/* Simpler than parsing ELF header */
		while (ret < 0) {
			ret = try_to_remap((void *)auxval, vdso_size);
			vdso_size += PAGE_SIZE;
		}

#ifdef __i386__
		/* Glibc is likely to explode now - exit with raw syscall */
		asm volatile ("int $0x80" : : "a" (__NR_exit), "b" (!!ret));
#else /* __x86_64__ */
		syscall(SYS_exit, ret);
#endif
	} else {
		int status;

		if (waitpid(child, &status, 0) != child ||
			!WIFEXITED(status)) {
			printf("[FAIL]\tmremap() of the vDSO does not work on this kernel!\n");
			return 1;
		} else if (WEXITSTATUS(status) != 0) {
			printf("[FAIL]\tChild failed with %d\n",
					WEXITSTATUS(status));
			return 1;
		}
		printf("[OK]\n");
	}

	return 0;
}