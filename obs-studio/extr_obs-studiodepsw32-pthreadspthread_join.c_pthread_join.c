#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ x; } ;
struct TYPE_10__ {scalar_t__ detachState; void* exitStatus; int /*<<< orphan*/  threadH; TYPE_1__ ptHandle; } ;
typedef  TYPE_2__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
struct TYPE_11__ {scalar_t__ x; int /*<<< orphan*/ * p; } ;
typedef  TYPE_3__ pthread_t ;

/* Variables and functions */
 int EDEADLK ; 
 int EINVAL ; 
 int ENOENT ; 
 int ESRCH ; 
 scalar_t__ PTHREAD_CREATE_DETACHED ; 
 int pthreadCancelableWait (int /*<<< orphan*/ ) ; 
 int pthread_detach (TYPE_3__) ; 
 scalar_t__ pthread_equal (TYPE_3__,TYPE_3__) ; 
 TYPE_3__ pthread_self () ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_thread_reuse_lock ; 

int
pthread_join (pthread_t thread, void **value_ptr)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function waits for 'thread' to terminate and
      *      returns the thread's exit value if 'value_ptr' is not
      *      NULL. This also detaches the thread on successful
      *      completion.
      *
      * PARAMETERS
      *      thread
      *              an instance of pthread_t
      *
      *      value_ptr
      *              pointer to an instance of pointer to void
      *
      *
      * DESCRIPTION
      *      This function waits for 'thread' to terminate and
      *      returns the thread's exit value if 'value_ptr' is not
      *      NULL. This also detaches the thread on successful
      *      completion.
      *      NOTE:   detached threads cannot be joined or canceled
      *
      * RESULTS
      *              0               'thread' has completed
      *              EINVAL          thread is not a joinable thread,
      *              ESRCH           no thread could be found with ID 'thread',
      *              ENOENT          thread couldn't find it's own valid handle,
      *              EDEADLK         attempt to join thread with self
      *
      * ------------------------------------------------------
      */
{
  int result;
  pthread_t self;
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
      result = 0;
    }

  ptw32_mcs_lock_release(&node);

  if (result == 0)
    {
      /* 
       * The target thread is joinable and can't be reused before we join it.
       */
      self = pthread_self();

      if (NULL == self.p)
	{
	  result = ENOENT;
	}
      else if (pthread_equal (self, thread))
	{
	  result = EDEADLK;
	}
      else
	{
	  /*
	   * Pthread_join is a cancelation point.
	   * If we are canceled then our target thread must not be
	   * detached (destroyed). This is guarranteed because
	   * pthreadCancelableWait will not return if we
	   * are canceled.
	   */
	  result = pthreadCancelableWait (tp->threadH);

	  if (0 == result)
	    {
	      if (value_ptr != NULL)
		{
		  *value_ptr = tp->exitStatus;
		}

	      /*
	       * The result of making multiple simultaneous calls to
	       * pthread_join() or pthread_detach() specifying the same
	       * target is undefined.
	       */
	      result = pthread_detach (thread);
	    }
	  else
	    {
	      result = ESRCH;
	    }
	}
    }

  return (result);

}