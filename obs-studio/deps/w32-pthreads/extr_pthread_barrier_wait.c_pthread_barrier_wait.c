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
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  TYPE_1__* pthread_barrier_t ;
struct TYPE_3__ {scalar_t__ nCurrentBarrierHeight; int nInitialBarrierHeight; int /*<<< orphan*/  proxynode; int /*<<< orphan*/  semBarrierBreeched; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 scalar_t__ PTW32_INTERLOCKED_INCREMENT_LONG (int /*<<< orphan*/ ) ; 
 scalar_t__ PTW32_OBJECT_INVALID ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_node_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ptw32_semwait (int /*<<< orphan*/ *) ; 
 int sem_post_multiple (int /*<<< orphan*/ *,int) ; 

int
pthread_barrier_wait (pthread_barrier_t * barrier)
{
  int result;
  pthread_barrier_t b;

  ptw32_mcs_local_node_t node;

  if (barrier == NULL || *barrier == (pthread_barrier_t) PTW32_OBJECT_INVALID)
    {
      return EINVAL;
    }

  ptw32_mcs_lock_acquire(&(*barrier)->lock, &node);

  b = *barrier;
  if (--b->nCurrentBarrierHeight == 0)
    {
      /*
       * We are the last thread to arrive at the barrier before it releases us.
       * Move our MCS local node to the global scope barrier handle so that the
       * last thread out (not necessarily us) can release the lock.
       */
      ptw32_mcs_node_transfer(&b->proxynode, &node);

      /*
       * Any threads that have not quite entered sem_wait below when the
       * multiple_post has completed will nevertheless continue through
       * the semaphore (barrier).
       */
      result = (b->nInitialBarrierHeight > 1
                ? sem_post_multiple (&(b->semBarrierBreeched),
				     b->nInitialBarrierHeight - 1) : 0);
    }
  else
    {
      ptw32_mcs_lock_release(&node);
      /*
       * Use the non-cancelable version of sem_wait().
       *
       * It is possible that all nInitialBarrierHeight-1 threads are
       * at this point when the last thread enters the barrier, resets
       * nCurrentBarrierHeight = nInitialBarrierHeight and leaves.
       * If pthread_barrier_destroy is called at that moment then the
       * barrier will be destroyed along with the semas.
       */
      result = ptw32_semwait (&(b->semBarrierBreeched));
    }

  if ((PTW32_INTERLOCKED_LONG)PTW32_INTERLOCKED_INCREMENT_LONG((PTW32_INTERLOCKED_LONGPTR)&b->nCurrentBarrierHeight)
		  == (PTW32_INTERLOCKED_LONG)b->nInitialBarrierHeight)
    {
      /*
       * We are the last thread to cross this barrier
       */
      ptw32_mcs_lock_release(&b->proxynode);
      if (0 == result)
        {
          result = PTHREAD_BARRIER_SERIAL_THREAD;
        }
    }

  return (result);
}