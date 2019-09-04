#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;
struct TYPE_8__ {int started; int threadnum; int count; } ;

/* Variables and functions */
 int NUMTHREADS ; 
 void* PTHREAD_CANCELED ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_cancel (TYPE_1__) ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (TYPE_1__,void**) ; 
 TYPE_1__ pthread_self () ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__* threadbag ; 

int
main()
{
  int failed = 0;
  int i;
  pthread_t t[NUMTHREADS + 1];

  assert((t[0] = pthread_self()).p != NULL);

  for (i = 1; i <= NUMTHREADS; i++)
    {
      threadbag[i].started = 0;
      threadbag[i].threadnum = i;
      assert(pthread_create(&t[i], NULL, mythread, (void *) &threadbag[i]) == 0);
    }

  /*
   * Code to control or munipulate child threads should probably go here.
   */
  Sleep(500);

  for (i = 1; i <= NUMTHREADS; i++)
    {
      assert(pthread_cancel(t[i]) == 0);
    }

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
      void* result = (void*)0;

      /*
       * The thread does not contain any cancelation points, so
       * a return value of PTHREAD_CANCELED indicates that async
       * cancelation occurred.
       */
      assert(pthread_join(t[i], &result) == 0);

      fail = (result == PTHREAD_CANCELED);

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