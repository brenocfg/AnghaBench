#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_12__ {long tv_sec; int tv_nsec; } ;
struct TYPE_11__ {long tv_sec; int tv_nsec; } ;
struct TYPE_10__ {char* nWaitersBlocked; char* nWaitersGone; char* nWaitersToUnblock; } ;
struct TYPE_9__ {int const millitm; scalar_t__ time; } ;
typedef  TYPE_1__ PTW32_STRUCT_TIMEB ;
typedef  int /*<<< orphan*/  LPLONG ;
typedef  int DWORD ;

/* Variables and functions */
 int InterlockedExchangeAdd (int /*<<< orphan*/ ,long) ; 
 int NUMTHREADS ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_1__*) ; 
 TYPE_7__ abstime ; 
 TYPE_6__ abstime2 ; 
 int /*<<< orphan*/  assert (int) ; 
 int awoken ; 
 TYPE_2__* cv ; 
 char** error_string ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_cond_broadcast (TYPE_2__**) ; 
 int pthread_cond_destroy (TYPE_2__**) ; 
 scalar_t__ pthread_cond_init (TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int timedout ; 

int
main()
{
  int i;
  pthread_t t[NUMTHREADS + 1];
  void* result = (void*)0;
  PTW32_STRUCT_TIMEB currSysTime;
  const DWORD NANOSEC_PER_MILLISEC = 1000000;

  assert(pthread_cond_init(&cv, NULL) == 0);

  assert(pthread_mutex_init(&mutex, NULL) == 0);

  /* get current system time */
  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = abstime2.tv_sec = (long)currSysTime.time + 5;
  abstime.tv_nsec = abstime2.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  assert(pthread_mutex_lock(&mutex) == 0);

  for (i = 1; i <= NUMTHREADS; i++)
    {
      assert(pthread_create(&t[i], NULL, mythread, (void *)(size_t)i) == 0);
    }

  assert(pthread_mutex_unlock(&mutex) == 0);

  for (i = 1; i <= NUMTHREADS; i++)
    {
      assert(pthread_join(t[i], &result) == 0);
	assert((int)(size_t)result == i);
      /*
       * Approximately 2/3rds of the threads are expected to time out.
       * Signal the remainder after some threads have woken up and exited
       * and while some are still waking up after timeout.
       * Also tests that redundant broadcasts don't return errors.
       */

//      assert(pthread_mutex_lock(&mutex) == 0);

      if (InterlockedExchangeAdd((LPLONG)&awoken, 0L) > NUMTHREADS/3)
        {
          assert(pthread_cond_broadcast(&cv) == 0);
        }

//      assert(pthread_mutex_unlock(&mutex) == 0);

    }

  assert(awoken == NUMTHREADS - timedout);

  {
  int result = pthread_cond_destroy(&cv);
  if (result != 0)
    {
      fprintf(stderr, "Result = %s\n", error_string[result]);
	fprintf(stderr, "\tWaitersBlocked = %ld\n", cv->nWaitersBlocked);
	fprintf(stderr, "\tWaitersGone = %ld\n", cv->nWaitersGone);
	fprintf(stderr, "\tWaitersToUnblock = %ld\n", cv->nWaitersToUnblock);
	fflush(stderr);
    }
  assert(result == 0);
  }

  assert(pthread_mutex_destroy(&mutex) == 0);

  return 0;
}