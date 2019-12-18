#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int work; int /*<<< orphan*/  mutex_started; int /*<<< orphan*/  mutex_ended; int /*<<< orphan*/  mutex_end; int /*<<< orphan*/  id; int /*<<< orphan*/  mutex_start; } ;
typedef  TYPE_1__ TC ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int do_work_unit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_todo ; 
 int nwork ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int todo ; 

__attribute__((used)) static int
print_server (void *ptr)
{
  int		mywork;
  int		n;
  TC		*tc = (TC *)ptr;

  assert(pthread_mutex_lock (&tc->mutex_started) == 0);

  for (;;)
    {
      assert(pthread_mutex_lock (&tc->mutex_start) == 0);
      assert(pthread_mutex_unlock (&tc->mutex_start) == 0);
      assert(pthread_mutex_lock (&tc->mutex_ended) == 0);
      assert(pthread_mutex_unlock (&tc->mutex_started) == 0);

      for (;;)
	{

	  /*
	   * get lock on todo list
	   */
	  assert(pthread_mutex_lock (&mutex_todo) == 0);

	  mywork = todo;
	  if (todo >= 0)
	    {
	      ++todo;
	      if (todo >= nwork)
		todo = -1;
	    }
	  assert(pthread_mutex_unlock (&mutex_todo) == 0);

	  if (mywork < 0)
	    break;

	  assert((n = do_work_unit (tc->id, mywork)) >= 0);
	  tc->work += n;
	}

      assert(pthread_mutex_lock (&tc->mutex_end) == 0);
      assert(pthread_mutex_unlock (&tc->mutex_end) == 0);
      assert(pthread_mutex_lock (&tc->mutex_started) == 0);
      assert(pthread_mutex_unlock (&tc->mutex_ended) == 0);

      if (-2 == mywork)
	break;
    }

  assert(pthread_mutex_unlock (&tc->mutex_started) == 0);

  return (0);
}