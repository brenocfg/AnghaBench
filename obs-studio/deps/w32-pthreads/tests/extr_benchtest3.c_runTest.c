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
 scalar_t__ GetDurationMilliSecs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float ITERATIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  currSysTimeStart ; 
 int /*<<< orphan*/  currSysTimeStop ; 
 scalar_t__ durationMilliSecs ; 
 int /*<<< orphan*/  ma ; 
 int /*<<< orphan*/  mx ; 
 scalar_t__ overHeadMilliSecs ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,float) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trylockThread ; 

void
runTest (char * testNameString, int mType)
{
  pthread_t t;

#ifdef PTW32_MUTEX_TYPES
  (void) pthread_mutexattr_settype(&ma, mType);
#endif
  assert(pthread_mutex_init(&mx, &ma) == 0);
  assert(pthread_mutex_lock(&mx) == 0);
  assert(pthread_create(&t, NULL, trylockThread, 0) == 0);
  assert(pthread_join(t, NULL) == 0);
  assert(pthread_mutex_unlock(&mx) == 0);
  assert(pthread_mutex_destroy(&mx) == 0);

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    testNameString,
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);
}