#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ x; } ;
struct TYPE_7__ {scalar_t__ detachState; scalar_t__ state; int /*<<< orphan*/  threadH; int /*<<< orphan*/  stateLock; TYPE_1__ ptHandle; } ;
typedef  TYPE_2__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
struct TYPE_8__ {scalar_t__ x; scalar_t__ p; } ;
typedef  TYPE_3__ pthread_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ PTHREAD_CREATE_DETACHED ; 
 scalar_t__ PTW32_FALSE ; 
 scalar_t__ PTW32_TRUE ; 
 scalar_t__ PThreadStateLast ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_threadDestroy (TYPE_3__) ; 
 int /*<<< orphan*/  ptw32_thread_reuse_lock ; 

int
pthread_detach (pthread_t thread)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function detaches the given thread.
      *
      * PARAMETERS
      *      thread
      *              an instance of a pthread_t
      *
      *
      * DESCRIPTION
      *      This function detaches the given thread. You may use it to
      *      detach the main thread or to detach a joinable thread.
      *      NOTE:   detached threads cannot be joined;
      *              storage is freed immediately on termination.
      *
      * RESULTS
      *              0               successfully detached the thread,
      *              EINVAL          thread is not a joinable thread,
      *              ENOSPC          a required resource has been exhausted,
      *              ESRCH           no thread could be found for 'thread',
      *
      * ------------------------------------------------------
      */
{
  int result;
  BOOL destroyIt = PTW32_FALSE;
  ptw32_thread_t * tp = (ptw32_thread_t *) thread.p;
  ptw32_mcs_local_node_t node;

  ptw32_mcs_lock_acquire(&ptw32_thread_reuse_lock, &node);

  if (NULL == tp
      || thread.x != tp->ptHandle.x)
    {
      result = ESRCH;
    }
  else if (PTHREAD_CREATE_DETACHED == tp->detachState)
    {
      result = EINVAL;
    }
  else
    {
      ptw32_mcs_local_node_t stateLock;
      /*
       * Joinable ptw32_thread_t structs are not scavenged until
       * a join or detach is done. The thread may have exited already,
       * but all of the state and locks etc are still there.
       */
      result = 0;

      ptw32_mcs_lock_acquire (&tp->stateLock, &stateLock);
      if (tp->state != PThreadStateLast)
        {
          tp->detachState = PTHREAD_CREATE_DETACHED;
        }
      else if (tp->detachState != PTHREAD_CREATE_DETACHED)
        {
          /*
           * Thread is joinable and has exited or is exiting.
           */
          destroyIt = PTW32_TRUE;
        }
      ptw32_mcs_lock_release (&stateLock);
    }

  ptw32_mcs_lock_release(&node);

  if (result == 0)
    {
      /* Thread is joinable */

      if (destroyIt)
	{
	  /* The thread has exited or is exiting but has not been joined or
	   * detached. Need to wait in case it's still exiting.
	   */
	  (void) WaitForSingleObject(tp->threadH, INFINITE);
	  ptw32_threadDestroy (thread);
	}
    }

  return (result);

}