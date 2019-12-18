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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int GetThreadPriority (int /*<<< orphan*/ ) ; 
 int PTW32TEST_MAXPRIORITIES ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int) ; 
 int THREAD_PRIORITY_HIGHEST ; 
 int THREAD_PRIORITY_LOWEST ; 
 int maxPrio ; 
 int minPrio ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_getw32threadhandle_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int* validPriorities ; 

void *
getValidPriorities(void * arg)
{
  int prioSet;
  pthread_t threadID = pthread_self();
  HANDLE threadH = pthread_getw32threadhandle_np(threadID);

  printf("Using GetThreadPriority\n");
  printf("%10s %10s\n", "Set value", "Get value");

  for (prioSet = minPrio;
       prioSet <= maxPrio;
       prioSet++)
    {
	/*
       * If prioSet is invalid then the threads priority is unchanged
       * from the previous value. Make the previous value a known
       * one so that we can check later.
       */
        if (prioSet < 0)
	  SetThreadPriority(threadH, THREAD_PRIORITY_LOWEST);
        else
	  SetThreadPriority(threadH, THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(threadH, prioSet);
	validPriorities[prioSet+(PTW32TEST_MAXPRIORITIES/2)] = GetThreadPriority(threadH);
	printf("%10d %10d\n", prioSet, validPriorities[prioSet+(PTW32TEST_MAXPRIORITIES/2)]);
    }

  return (void *) 0;
}