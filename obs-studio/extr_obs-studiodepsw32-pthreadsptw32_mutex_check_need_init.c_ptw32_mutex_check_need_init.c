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
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  int /*<<< orphan*/ * pthread_mutex_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/ * PTHREAD_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/ * PTHREAD_RECURSIVE_MUTEX_INITIALIZER ; 
 int pthread_mutex_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_errorcheck_mutexattr ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mutex_test_init_lock ; 
 int /*<<< orphan*/  ptw32_recursive_mutexattr ; 

int
ptw32_mutex_check_need_init (pthread_mutex_t * mutex)
{
  register int result = 0;
  register pthread_mutex_t mtx;
  ptw32_mcs_local_node_t node;

  ptw32_mcs_lock_acquire(&ptw32_mutex_test_init_lock, &node);

  /*
   * We got here possibly under race
   * conditions. Check again inside the critical section
   * and only initialise if the mutex is valid (not been destroyed).
   * If a static mutex has been destroyed, the application can
   * re-initialise it only by calling pthread_mutex_init()
   * explicitly.
   */
  mtx = *mutex;

  if (mtx == PTHREAD_MUTEX_INITIALIZER)
    {
      result = pthread_mutex_init (mutex, NULL);
    }
  else if (mtx == PTHREAD_RECURSIVE_MUTEX_INITIALIZER)
    {
      result = pthread_mutex_init (mutex, &ptw32_recursive_mutexattr);
    }
  else if (mtx == PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
    {
      result = pthread_mutex_init (mutex, &ptw32_errorcheck_mutexattr);
    }
  else if (mtx == NULL)
    {
      /*
       * The mutex has been destroyed while we were waiting to
       * initialise it, so the operation that caused the
       * auto-initialisation should fail.
       */
      result = EINVAL;
    }

  ptw32_mcs_lock_release(&node);

  return (result);
}