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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int MAP_32BIT ; 
 int MAP_ANONYMOUS ; 
 unsigned char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  call32_from_64 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 unsigned char* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ss ; 
 int /*<<< orphan*/  threadproc ; 
 int /*<<< orphan*/  usleep (int) ; 

int main()
{
	/*
	 * Start a busy-looping thread on the same CPU we're on.
	 * For simplicity, just stick everything to CPU 0.  This will
	 * fail in some containers, but that's probably okay.
	 */
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		printf("[WARN]\tsched_setaffinity failed\n");

	pthread_t thread;
	if (pthread_create(&thread, 0, threadproc, 0) != 0)
		err(1, "pthread_create");

#ifdef __x86_64__
	unsigned char *stack32 = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
				      MAP_32BIT | MAP_ANONYMOUS | MAP_PRIVATE,
				      -1, 0);
	if (stack32 == MAP_FAILED)
		err(1, "mmap");
#endif

	printf("[RUN]\tSyscalls followed by SS validation\n");

	for (int i = 0; i < 1000; i++) {
		/*
		 * Go to sleep and return using sysret (if we're 64-bit
		 * or we're 32-bit on AMD on a 64-bit kernel).  On AMD CPUs,
		 * SYSRET doesn't fix up the cached SS descriptor, so the
		 * kernel needs some kind of workaround to make sure that we
		 * end the system call with a valid stack segment.  This
		 * can be a confusing failure because the SS *selector*
		 * is the same regardless.
		 */
		usleep(2);

#ifdef __x86_64__
		/*
		 * On 32-bit, just doing a syscall through glibc is enough
		 * to cause a crash if our cached SS descriptor is invalid.
		 * On 64-bit, it's not, so try extra hard.
		 */
		call32_from_64(stack32 + 4088, test_ss);
#endif
	}

	printf("[OK]\tWe survived\n");

#ifdef __x86_64__
	munmap(stack32, 4096);
#endif

	return 0;
}