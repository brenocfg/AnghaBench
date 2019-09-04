#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_12__ {long tv_sec; int tv_nsec; } ;
struct TYPE_11__ {char* nWaitersBlocked; char* nWaitersGone; char* nWaitersToUnblock; } ;
struct TYPE_10__ {int const millitm; scalar_t__ time; } ;
typedef  TYPE_1__ PTW32_STRUCT_TIMEB ;
typedef  int DWORD ;

/* Variables and functions */
 int NUMTHREADS ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_1__*) ; 
 TYPE_8__ abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 int awoken ; 
 TYPE_2__* cv ; 
 TYPE_2__* cv1 ; 
 char** error_string ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex1 ; 
 int /*<<< orphan*/  mythread ; 
 int pthread_cond_destroy (TYPE_2__**) ; 
 scalar_t__ pthread_cond_init (TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_signal (TYPE_2__**) ; 
 scalar_t__ pthread_cond_wait (TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int signaled ; 
 int /*<<< orphan*/  stderr ; 
 int timedout ; 
 int waiting ; 

int
main()
{
  int i;
  pthread_t t[NUMTHREADS + 1];
  void* result = (void*)0;
  PTW32_STRUCT_TIMEB currSysTime;
  const DWORD NANOSEC_PER_MILLISEC = 1000000;

  assert(pthread_cond_init(&cv, NULL) == 0);
  assert(pthread_cond_init(&cv1, NULL) == 0);

  assert(pthread_mutex_init(&mutex, NULL) == 0);
  assert(pthread_mutex_init(&mutex1, NULL) == 0);

  /* get current system time */
  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = (long)currSysTime.time;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  abstime.tv_sec += 5;

  assert(pthread_mutex_lock(&mutex1) == 0);

  for (i = 1; i <= NUMTHREADS; i++)
    {
      assert(pthread_create(&t[i], NULL, mythread, (void *)(size_t)i) == 0);
    }

  do {
    assert(pthread_cond_wait(&cv1,&mutex1) == 0);
  } while ( NUMTHREADS > waiting );

  assert(pthread_mutex_unlock(&mutex1) == 0);

  for (i = NUMTHREADS/3; i <= 2*NUMTHREADS/3; i++)
    {
//      assert(pthread_mutex_lock(&mutex) == 0);
      assert(pthread_cond_signal(&cv) == 0);
//      assert(pthread_mutex_unlock(&mutex) == 0);

      signaled++;
    }

  for (i = 1; i <= NUMTHREADS; i++)
    {
      assert(pthread_join(t[i], &result) == 0);
        assert((int)(size_t)result == i);
    }

      fprintf(stderr, "awk = %d\n", awoken);
      fprintf(stderr, "sig = %d\n", signaled);
      fprintf(stderr, "tot = %d\n", timedout);

  assert(signaled == awoken);
  assert(timedout == NUMTHREADS - signaled);

  assert(pthread_cond_destroy(&cv1) == 0);

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

  assert(pthread_mutex_destroy(&mutex1) == 0);
  assert(pthread_mutex_destroy(&mutex) == 0);

  return 0;
}