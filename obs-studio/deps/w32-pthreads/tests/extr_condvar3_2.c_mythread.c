#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tv_sec; } ;
struct TYPE_4__ {int tv_sec; } ;
typedef  int /*<<< orphan*/  LPLONG ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ ) ; 
 TYPE_3__ abstime ; 
 TYPE_1__ abstime2 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  awoken ; 
 int /*<<< orphan*/  cv ; 
 int /*<<< orphan*/  mutex ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timedout ; 

void *
mythread(void * arg)
{
  int result;

  assert(pthread_mutex_lock(&mutex) == 0);

  abstime2.tv_sec = abstime.tv_sec;

  if ((int) (size_t)arg % 3 == 0)
    {
      abstime2.tv_sec += 2;
    }

  result = pthread_cond_timedwait(&cv, &mutex, &abstime2);
  assert(pthread_mutex_unlock(&mutex) == 0);
  if (result == ETIMEDOUT)
    {
      InterlockedIncrement((LPLONG)&timedout);
    }
  else
    {
      InterlockedIncrement((LPLONG)&awoken);
    }


  return arg;
}