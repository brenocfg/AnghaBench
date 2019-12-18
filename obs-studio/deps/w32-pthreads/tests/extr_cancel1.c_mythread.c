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
 int PTHREAD_CANCEL_ASYNCHRONOUS ; 
 int PTHREAD_CANCEL_DEFERRED ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_setcancelstate (int,int*) ; 
 scalar_t__ pthread_setcanceltype (int,int*) ; 
 TYPE_1__* threadbag ; 

void *
mythread(void * arg)
{
  bag_t * bag = (bag_t *) arg;

  assert(bag == &threadbag[bag->threadnum]);
  assert(bag->started == 0);
  bag->started = 1;

  /* ... */
  {
    int oldstate;
    int oldtype;

    assert(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate) == 0);
    assert(oldstate == PTHREAD_CANCEL_ENABLE); /* Check default */
    assert(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) == 0);
    assert(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) == 0);
    assert(pthread_setcancelstate(oldstate, &oldstate) == 0);
    assert(oldstate == PTHREAD_CANCEL_DISABLE); /* Check setting */

    assert(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype) == 0);
    assert(oldtype == PTHREAD_CANCEL_DEFERRED); /* Check default */
    assert(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL) == 0);
    assert(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) == 0);
    assert(pthread_setcanceltype(oldtype, &oldtype) == 0);
    assert(oldtype == PTHREAD_CANCEL_ASYNCHRONOUS); /* Check setting */
  }

  return 0;
}