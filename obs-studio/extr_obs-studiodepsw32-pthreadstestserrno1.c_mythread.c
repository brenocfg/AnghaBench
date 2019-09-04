#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t threadnum; int started; } ;
typedef  TYPE_1__ bag_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t errno ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_here ; 
 TYPE_1__* threadbag ; 

void *
mythread(void * arg)
{
  bag_t * bag = (bag_t *) arg;

  assert(bag == &threadbag[bag->threadnum]);
  assert(bag->started == 0);
  bag->started = 1;

  errno = bag->threadnum;

  Sleep(1000);

  pthread_mutex_lock(&stop_here);

  assert(errno == bag->threadnum);

  pthread_mutex_unlock(&stop_here);

  Sleep(1000);

  return 0;
}