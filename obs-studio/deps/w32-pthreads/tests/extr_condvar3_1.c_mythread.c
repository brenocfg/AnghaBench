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
 int ETIMEDOUT ; 
 int /*<<< orphan*/  abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  awoken ; 
 int /*<<< orphan*/  cv ; 
 int /*<<< orphan*/  cv1 ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex1 ; 
 scalar_t__ pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timedout ; 
 int /*<<< orphan*/  waiting ; 

void *
mythread(void * arg)
{
  int result;

  assert(pthread_mutex_lock(&mutex1) == 0);
  ++waiting;
  assert(pthread_mutex_unlock(&mutex1) == 0);
  assert(pthread_cond_signal(&cv1) == 0);

  assert(pthread_mutex_lock(&mutex) == 0);
  result = pthread_cond_timedwait(&cv, &mutex, &abstime);
  if (result == ETIMEDOUT)
    {
      timedout++;
    }
  else
    {
      awoken++;
    }
  assert(pthread_mutex_unlock(&mutex) == 0);

  return arg;
}