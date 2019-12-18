#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
struct TYPE_3__ {int started; int threadnum; int count; TYPE_2__ self; } ;
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 scalar_t__ GetExitCodeThread (scalar_t__,int /*<<< orphan*/ ) ; 
 int NUMTHREADS ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  Win32thread ; 
 scalar_t__ _beginthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ pthread_kill (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* threadbag ; 

int
main()
{
  int failed = 0;
  int i;
  HANDLE h[NUMTHREADS + 1];
  unsigned thrAddr; /* Dummy variable to pass a valid location to _beginthreadex (Win98). */

  for (i = 1; i <= NUMTHREADS; i++)
    {
      threadbag[i].started = 0;
      threadbag[i].threadnum = i;
#if ! defined (__MINGW32__) || defined (__MSVCRT__)
      h[i] = (HANDLE) _beginthreadex(NULL, 0, Win32thread, (void *) &threadbag[i], 0, &thrAddr);
#else
      h[i] = (HANDLE) _beginthread(Win32thread, 0, (void *) &threadbag[i]);
#endif
    }

  /*
   * Code to control or munipulate child threads should probably go here.
   */
  Sleep(500);

  /*
   * Give threads time to run.
   */
  Sleep(NUMTHREADS * 100);

  /*
   * Standard check that all threads started.
   */
  for (i = 1; i <= NUMTHREADS; i++)
    { 
      if (!threadbag[i].started)
	{
	  failed |= !threadbag[i].started;
	  fprintf(stderr, "Thread %d: started %d\n", i, threadbag[i].started);
	}
    }

  assert(!failed);

  /*
   * Check any results here. Set "failed" and only print output on failure.
   */
  failed = 0;
  for (i = 1; i <= NUMTHREADS; i++)
    {
      int fail = 0;
      int result = 0;

#if ! defined (__MINGW32__) || defined (__MSVCRT__)
      assert(GetExitCodeThread(h[i], (LPDWORD) &result) == TRUE);
#else
      /*
       * Can't get a result code.
       */
      result = 1;
#endif

      assert(threadbag[i].self.p != NULL && pthread_kill(threadbag[i].self, 0) == ESRCH);

      fail = (result != 1);

      if (fail)
	{
	  fprintf(stderr, "Thread %d: started %d: count %d\n",
		  i,
		  threadbag[i].started,
		  threadbag[i].count);
	}
      failed = (failed || fail);
    }

  assert(!failed);

  /*
   * Success.
   */
  return 0;
}