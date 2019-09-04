#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ x; } ;
struct TYPE_6__ {int /*<<< orphan*/ * threadH; TYPE_1__ ptHandle; } ;
typedef  TYPE_2__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ p; } ;
typedef  TYPE_3__ pthread_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_thread_reuse_lock ; 

int
pthread_kill (pthread_t thread, int sig)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function requests that a signal be delivered to the
      *      specified thread. If sig is zero, error checking is
      *      performed but no signal is actually sent such that this
      *      function can be used to check for a valid thread ID.
      *
      * PARAMETERS
      *      thread  reference to an instances of pthread_t
      *      sig     signal. Currently only a value of 0 is supported.
      *
      *
      * DESCRIPTION
      *      This function requests that a signal be delivered to the
      *      specified thread. If sig is zero, error checking is
      *      performed but no signal is actually sent such that this
      *      function can be used to check for a valid thread ID.
      *
      * RESULTS
      *              ESRCH           the thread is not a valid thread ID,
      *              EINVAL          the value of the signal is invalid
      *                              or unsupported.
      *              0               the signal was successfully sent.
      *
      * ------------------------------------------------------
      */
{
  int result = 0;
  ptw32_thread_t * tp;
  ptw32_mcs_local_node_t node;

  ptw32_mcs_lock_acquire(&ptw32_thread_reuse_lock, &node);

  tp = (ptw32_thread_t *) thread.p;

  if (NULL == tp
      || thread.x != tp->ptHandle.x
      || NULL == tp->threadH)
    {
      result = ESRCH;
    }

  ptw32_mcs_lock_release(&node);

  if (0 == result && 0 != sig)
    {
      /*
       * Currently does not support any signals.
       */
      result = EINVAL;
    }

  return result;

}