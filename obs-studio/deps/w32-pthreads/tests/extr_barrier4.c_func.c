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

/* Variables and functions */
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  barrier ; 
 char** error_string ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx ; 
 int /*<<< orphan*/  otherThreadCount ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serialThreadCount ; 
 int /*<<< orphan*/  stdout ; 

void *
func(void * arg)
{
  int result = pthread_barrier_wait(&barrier);

  assert(pthread_mutex_lock(&mx) == 0);

  if (result == PTHREAD_BARRIER_SERIAL_THREAD)
    {
      serialThreadCount++;
    }
  else if (0 == result)
    {
      otherThreadCount++;
    }
  else
    {
      printf("Barrier wait failed: error = %s\n", error_string[result]);
      fflush(stdout);
      return NULL;
    }
  assert(pthread_mutex_unlock(&mx) == 0);

  return NULL;
}