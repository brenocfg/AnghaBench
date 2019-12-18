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
struct TYPE_3__ {size_t threadnum; int started; int count; } ;
typedef  TYPE_1__ bag_t ;

/* Variables and functions */
 scalar_t__ PTHREAD_CANCELED ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_DEFERRED ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_setcancelstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_setcanceltype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* threadbag ; 

void *
mythread(void * arg)
{
  void* result = (void*)((int)(size_t)PTHREAD_CANCELED + 1);
  bag_t * bag = (bag_t *) arg;

  assert(bag == &threadbag[bag->threadnum]);
  assert(bag->started == 0);
  bag->started = 1;

  /* Set to known state and type */

  assert(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) == 0);

  assert(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL) == 0);

  /*
   * We wait up to 2 seconds, waking every 0.1 seconds,
   * for a cancelation to be applied to us.
   */
  for (bag->count = 0; bag->count < 20; bag->count++)
    Sleep(100);

  return result;
}