#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;
struct TYPE_14__ {long tv_sec; int tv_nsec; } ;
struct TYPE_13__ {int /*<<< orphan*/ * notbusy; int /*<<< orphan*/ * lock; scalar_t__ shared; } ;
struct TYPE_12__ {int started; int threadnum; } ;
struct TYPE_11__ {int const millitm; scalar_t__ time; } ;
typedef  TYPE_2__ PTW32_STRUCT_TIMEB ;
typedef  int DWORD ;

/* Variables and functions */
 int NUMTHREADS ; 
 int /*<<< orphan*/ * PTHREAD_COND_INITIALIZER ; 
 int /*<<< orphan*/ * PTHREAD_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 TYPE_8__ abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 int awoken ; 
 TYPE_7__ cvthing ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_cond_broadcast (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (TYPE_1__,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ **) ; 
 TYPE_1__ pthread_self () ; 
 int /*<<< orphan*/ * start_flag ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_3__* threadbag ; 

int
main()
{
  int failed = 0;
  int i;
  int first, last;
  pthread_t t[NUMTHREADS + 1];

  PTW32_STRUCT_TIMEB currSysTime;
  const DWORD NANOSEC_PER_MILLISEC = 1000000;

  assert((t[0] = pthread_self()).p != NULL);

  assert(cvthing.notbusy == PTHREAD_COND_INITIALIZER);

  assert(cvthing.lock == PTHREAD_MUTEX_INITIALIZER);

  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = (long)currSysTime.time;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  abstime.tv_sec += 10;

  assert((t[0] = pthread_self()).p != NULL);

  awoken = 0;

  for (first = 1, last = NUMTHREADS / 2;
       first < NUMTHREADS;
       first = last + 1, last = NUMTHREADS)
    {
      assert(pthread_mutex_lock(&start_flag) == 0);

      for (i = first; i <= last; i++)
	{
	  threadbag[i].started = 0;
	  threadbag[i].threadnum = i;
	  assert(pthread_create(&t[i], NULL, mythread, (void *) &threadbag[i]) == 0);
	}

      /*
       * Code to control or munipulate child threads should probably go here.
       */
      cvthing.shared = 0;

      assert(pthread_mutex_unlock(&start_flag) == 0);

      /*
       * Give threads time to start.
       */
      Sleep(100);

      assert(pthread_mutex_lock(&cvthing.lock) == 0);
      cvthing.shared++;
      assert(pthread_mutex_unlock(&cvthing.lock) == 0);

      assert(pthread_cond_broadcast(&cvthing.notbusy) == 0);

      /*
       * Give threads time to complete.
       */
      for (i = first; i <= last; i++)
	{
	  assert(pthread_join(t[i], NULL) == 0);
	}

      assert(awoken == (i - 1));
    }


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

  /* 
   * Cleanup the CV.
   */
  
  assert(pthread_mutex_destroy(&cvthing.lock) == 0);

  assert(cvthing.lock == NULL);

  assert(pthread_cond_destroy(&cvthing.notbusy) == 0);

  assert(cvthing.notbusy == NULL);

  assert(!failed);

  /*
   * Check any results here.
   */

  assert(awoken == NUMTHREADS);

  /*
   * Success.
   */
  return 0;
}