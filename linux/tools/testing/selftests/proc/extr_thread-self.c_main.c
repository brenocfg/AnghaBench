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

/* Variables and functions */
 int CLONE_SIGHAND ; 
 int CLONE_THREAD ; 
 int CLONE_VM ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ clone (int /*<<< orphan*/  (*) (void*),void*,int,void*) ; 
 int /*<<< orphan*/  f (void*) ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause () ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int main(void)
{
	const int PAGE_SIZE = sysconf(_SC_PAGESIZE);
	pid_t pid;
	void *stack;

	/* main thread */
	f((void *)0);

	stack = mmap(NULL, 2 * PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	assert(stack != MAP_FAILED);
	/* side thread */
	pid = clone(f, stack + PAGE_SIZE, CLONE_THREAD|CLONE_SIGHAND|CLONE_VM, (void *)1);
	assert(pid > 0);
	pause();

	return 0;
}