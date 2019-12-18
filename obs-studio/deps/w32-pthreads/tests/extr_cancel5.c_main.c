#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_2__ {int started; int threadnum; int count; } ;

/* Variables and functions */
 int NUMTHREADS ; 
 void* PTHREAD_CANCELED ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* threadbag ; 

int
main ()
{
  int failed = 0;
  int i;
  pthread_t t[NUMTHREADS + 1];

  for (i = 1; i <= NUMTHREADS; i++)
    {
      threadbag[i].started = 0;
      threadbag[i].threadnum = i;
      assert (pthread_create (&t[i], NULL, mythread, (void *) &threadbag[i])
	      == 0);
    }

  /*
   * Code to control or munipulate child threads should probably go here.
   */
  Sleep (500);

  for (i = 1; i <= NUMTHREADS; i++)
    {
      assert (pthread_cancel (t[i]) == 0);
    }

  /*
   * Give threads time to run.
   */
  Sleep (NUMTHREADS * 100);

  /*
   * Standard check that all threads started.
   */
  for (i = 1; i <= NUMTHREADS; i++)
    {
      if (!threadbag[i].started)
	{
	  failed |= !threadbag[i].started;
	  fprintf (stderr, "Thread %d: started %d\n", i,
		   threadbag[i].started);
	}
    }

  assert (!failed);

  /*
   * Check any results here. Set "failed" and only print output on failure.
   */
  failed = 0;
  for (i = 1; i <= NUMTHREADS; i++)
    {
      int fail = 0;
      void* result = (void*)((int)(size_t)PTHREAD_CANCELED + 1);

      /*
       * The thread does not contain any cancelation points, so
       * a return value of PTHREAD_CANCELED confirms that async
       * cancelation succeeded.
       */
      assert (pthread_join (t[i], &result) == 0);

      fail = (result != PTHREAD_CANCELED);

      if (fail)
	{
	  fprintf (stderr, "Thread %d: started %d: count %d\n",
		   i, threadbag[i].started, threadbag[i].count);
	}
      failed = (failed || fail);
    }

  assert (!failed);

  /*
   * Success.
   */
  return 0;
}