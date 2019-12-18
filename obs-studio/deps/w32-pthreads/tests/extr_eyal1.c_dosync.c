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
struct TYPE_2__ {int /*<<< orphan*/  mutex_ended; int /*<<< orphan*/  mutex_end; int /*<<< orphan*/  mutex_start; int /*<<< orphan*/  mutex_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int nthreads ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tcs ; 

__attribute__((used)) static void
dosync (void)
{
  int		i;

  for (i = 0; i < nthreads; ++i)
    {
      assert(pthread_mutex_lock (&tcs[i].mutex_end) == 0);
      assert(pthread_mutex_unlock (&tcs[i].mutex_start) == 0);
      assert(pthread_mutex_lock (&tcs[i].mutex_started) == 0);
      assert(pthread_mutex_unlock (&tcs[i].mutex_started) == 0);
    }

  /*
   * Now threads do their work
   */
  for (i = 0; i < nthreads; ++i)
    {
      assert(pthread_mutex_lock (&tcs[i].mutex_start) == 0);
      assert(pthread_mutex_unlock (&tcs[i].mutex_end) == 0);
      assert(pthread_mutex_lock (&tcs[i].mutex_ended) == 0);
      assert(pthread_mutex_unlock (&tcs[i].mutex_ended) == 0);
    }
}