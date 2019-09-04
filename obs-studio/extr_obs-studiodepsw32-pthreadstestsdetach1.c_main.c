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

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int NUMTHREADS ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  func ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char * argv[])
{
	pthread_t id[NUMTHREADS];
	int i;

	/* Create a few threads and then exit. */
	for (i = 0; i < NUMTHREADS; i++)
	  {
	    assert(pthread_create(&id[i], NULL, func, (void *)(size_t)i) == 0);
	  }

	/* Some threads will finish before they are detached, some after. */
	Sleep(NUMTHREADS/2 * 10 + 50);

	for (i = 0; i < NUMTHREADS; i++)
	  {
	    assert(pthread_detach(id[i]) == 0);
	  }

	Sleep(NUMTHREADS * 10 + 100);

	/*
	 * Check that all threads are now invalid.
	 * This relies on unique thread IDs - e.g. works with
	 * pthreads-w32 or Solaris, but may not work for Linux, BSD etc.
	 */
	for (i = 0; i < NUMTHREADS; i++)
	  {
	    assert(pthread_kill(id[i], 0) == ESRCH);
	  }

	/* Success. */
	return 0;
}