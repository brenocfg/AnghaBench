#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ p; scalar_t__ x; } ;
typedef  TYPE_1__ pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int NUMTHREADS ; 
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  func ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_equal (TYPE_1__,TYPE_1__) ; 
 scalar_t__ pthread_join (TYPE_1__,void**) ; 
 int washere ; 

int
main()
{
  pthread_t t,
            last_t;
  pthread_attr_t attr;
  void * result = NULL;
  int i;

  assert(pthread_attr_init(&attr) == 0);;
  assert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) == 0);

  washere = 0;
  assert(pthread_create(&t, &attr, func, NULL) == 0);
  assert(pthread_join(t, &result) == 0);;
  assert((int)(size_t)result == 0);
  assert(washere == 1);
  last_t = t;

  for (i = 1; i < NUMTHREADS; i++)
    {
      washere = 0;
      assert(pthread_create(&t, &attr, func, (void *)(size_t)i) == 0);
      pthread_join(t, &result);
      assert((int)(size_t) result == i);
      assert(washere == 1);
      /* thread IDs should be unique */
      assert(!pthread_equal(t, last_t));
      /* thread struct pointers should be the same */
      assert(t.p == last_t.p);
      /* thread handle reuse counter should be different by one */
      assert(t.x == last_t.x+1);
      last_t = t;
    }

  return 0;
}