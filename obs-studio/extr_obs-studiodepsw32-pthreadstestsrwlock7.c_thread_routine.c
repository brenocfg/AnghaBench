#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int seed; int changed; scalar_t__ thread_num; int /*<<< orphan*/  reads; int /*<<< orphan*/  updates; } ;
typedef  TYPE_1__ thread_t ;
struct TYPE_4__ {scalar_t__ data; int /*<<< orphan*/  lock; int /*<<< orphan*/  updates; } ;

/* Variables and functions */
 int DATASIZE ; 
 int ITERATIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* data ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int rand_r (int*) ; 
 int /*<<< orphan*/  stdout ; 

void *thread_routine (void *arg)
{
  thread_t *self = (thread_t*)arg;
  int iteration;
  int element = 0;
  int seed = self->seed;
  int interval = 1 + rand_r (&seed) % 71;

  self->changed = 0;

  for (iteration = 0; iteration < ITERATIONS; iteration++)
    {
      if (iteration % (ITERATIONS / 10) == 0)
        {
          putchar('.');
          fflush(stdout);
        }
      /*
       * Each "self->interval" iterations, perform an
       * update operation (write lock instead of read
       * lock).
       */
      if ((iteration % interval) == 0)
        {
          assert(pthread_rwlock_wrlock (&data[element].lock) == 0);
          data[element].data = self->thread_num;
          data[element].updates++;
          self->updates++;
	  interval = 1 + rand_r (&seed) % 71;
          assert(pthread_rwlock_unlock (&data[element].lock) == 0);
        } else {
          /*
           * Look at the current data element to see whether
           * the current thread last updated it. Count the
           * times, to report later.
           */
          assert(pthread_rwlock_rdlock (&data[element].lock) == 0);

          self->reads++;

          if (data[element].data != self->thread_num)
            {
              self->changed++;
	      interval = 1 + self->changed % 71;
            }

          assert(pthread_rwlock_unlock (&data[element].lock) == 0);
        }

      element = (element + 1) % DATASIZE;

    }

  return NULL;
}