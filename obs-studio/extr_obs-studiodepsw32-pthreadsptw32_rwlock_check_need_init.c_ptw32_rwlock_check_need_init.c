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
typedef  int /*<<< orphan*/ * pthread_rwlock_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * PTHREAD_RWLOCK_INITIALIZER ; 
 int pthread_rwlock_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_rwlock_test_init_lock ; 

int
ptw32_rwlock_check_need_init (pthread_rwlock_t * rwlock)
{
  int result = 0;
  ptw32_mcs_local_node_t node;

  /*
   * The following guarded test is specifically for statically
   * initialised rwlocks (via PTHREAD_RWLOCK_INITIALIZER).
   */
  ptw32_mcs_lock_acquire(&ptw32_rwlock_test_init_lock, &node);

  /*
   * We got here possibly under race
   * conditions. Check again inside the critical section
   * and only initialise if the rwlock is valid (not been destroyed).
   * If a static rwlock has been destroyed, the application can
   * re-initialise it only by calling pthread_rwlock_init()
   * explicitly.
   */
  if (*rwlock == PTHREAD_RWLOCK_INITIALIZER)
    {
      result = pthread_rwlock_init (rwlock, NULL);
    }
  else if (*rwlock == NULL)
    {
      /*
       * The rwlock has been destroyed while we were waiting to
       * initialise it, so the operation that caused the
       * auto-initialisation should fail.
       */
      result = EINVAL;
    }

  ptw32_mcs_lock_release(&node);

  return result;
}