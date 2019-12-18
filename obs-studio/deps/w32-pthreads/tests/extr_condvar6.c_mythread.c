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
struct TYPE_4__ {size_t threadnum; int started; } ;
typedef  TYPE_1__ bag_t ;
struct TYPE_5__ {scalar_t__ shared; int /*<<< orphan*/  lock; int /*<<< orphan*/  notbusy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  awoken ; 
 TYPE_3__ cvthing ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_flag ; 
 TYPE_1__* threadbag ; 

void *
mythread(void * arg)
{
  bag_t * bag = (bag_t *) arg;

  assert(bag == &threadbag[bag->threadnum]);
  assert(bag->started == 0);
  bag->started = 1;

  /* Wait for the start gun */
  assert(pthread_mutex_lock(&start_flag) == 0);
  assert(pthread_mutex_unlock(&start_flag) == 0);

  assert(pthread_mutex_lock(&cvthing.lock) == 0);

  while (! (cvthing.shared > 0))
    assert(pthread_cond_timedwait(&cvthing.notbusy, &cvthing.lock, &abstime) == 0);

  assert(cvthing.shared > 0);

  awoken++;

  assert(pthread_mutex_unlock(&cvthing.lock) == 0);

  return (void *) 0;
}