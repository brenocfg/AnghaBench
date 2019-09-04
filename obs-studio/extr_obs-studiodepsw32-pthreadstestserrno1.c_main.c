#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;
struct TYPE_6__ {int started; int threadnum; } ;

/* Variables and functions */
 int NUMTHREADS ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ pthread_self () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_here ; 
 TYPE_2__* threadbag ; 

int
main()
{
  int failed = 0;
  int i;
  pthread_t t[NUMTHREADS + 1];

  pthread_mutex_lock(&stop_here);
  errno = 0;

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
  Sleep(2000);
  pthread_mutex_unlock(&stop_here);

  /*
   * Give threads time to run.
   */
  Sleep(NUMTHREADS * 1000);

  /*
   * Standard check that all threads started.
   */
  for (i = 1; i <= NUMTHREADS; i++)
    { 
      failed = !threadbag[i].started;

      if (failed)
	{
	  fprintf(stderr, "Thread %d: started %d\n", i, threadbag[i].started);
	}
    }

  assert(!failed);

  /*
   * Check any results here. Set "failed" and only print ouput on failure.
   */
  for (i = 1; i <= NUMTHREADS; i++)
    { 
      /* ... */
    }

  assert(!failed);

  /*
   * Success.
   */
  return 0;
}