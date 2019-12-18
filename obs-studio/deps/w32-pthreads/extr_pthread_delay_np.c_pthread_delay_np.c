#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {long tv_sec; long tv_nsec; } ;
struct TYPE_4__ {scalar_t__ cancelState; scalar_t__ state; int /*<<< orphan*/  stateLock; int /*<<< orphan*/  cancelEvent; } ;
typedef  TYPE_1__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ pthread_t ;
typedef  long DWORD ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ESRCH ; 
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  PTW32_EPS_CANCEL ; 
 scalar_t__ PThreadStateCanceling ; 
 int /*<<< orphan*/  Sleep (long) ; 
 long WAIT_OBJECT_0 ; 
 long WAIT_TIMEOUT ; 
 long WaitForSingleObject (int /*<<< orphan*/ ,long) ; 
 TYPE_2__ pthread_self () ; 
 int /*<<< orphan*/  pthread_testcancel () ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_throw (int /*<<< orphan*/ ) ; 

int
pthread_delay_np (struct timespec *interval)
{
  DWORD wait_time;
  DWORD secs_in_millisecs;
  DWORD millisecs;
  DWORD status;
  pthread_t self;
  ptw32_thread_t * sp;

  if (interval == NULL)
    {
      return EINVAL;
    }

  if (interval->tv_sec == 0L && interval->tv_nsec == 0L)
    {
      pthread_testcancel ();
      Sleep (0);
      pthread_testcancel ();
      return (0);
    }

  /* convert secs to millisecs */
  secs_in_millisecs = (DWORD)interval->tv_sec * 1000L;

  /* convert nanosecs to millisecs (rounding up) */
  millisecs = (interval->tv_nsec + 999999L) / 1000000L;

#if defined(__WATCOMC__)
#pragma disable_message (124)
#endif

  /*
   * Most compilers will issue a warning 'comparison always 0'
   * because the variable type is unsigned, but we need to keep this
   * for some reason I can't recall now.
   */
  if (0 > (wait_time = secs_in_millisecs + millisecs))
    {
      return EINVAL;
    }

#if defined(__WATCOMC__)
#pragma enable_message (124)
#endif

  if (NULL == (self = pthread_self ()).p)
    {
      return ENOMEM;
    }

  sp = (ptw32_thread_t *) self.p;

  if (sp->cancelState == PTHREAD_CANCEL_ENABLE)
    {
      /*
       * Async cancelation won't catch us until wait_time is up.
       * Deferred cancelation will cancel us immediately.
       */
      if (WAIT_OBJECT_0 ==
	  (status = WaitForSingleObject (sp->cancelEvent, wait_time)))
	{
          ptw32_mcs_local_node_t stateLock;
	  /*
	   * Canceling!
	   */
	  ptw32_mcs_lock_acquire (&sp->stateLock, &stateLock);
	  if (sp->state < PThreadStateCanceling)
	    {
	      sp->state = PThreadStateCanceling;
	      sp->cancelState = PTHREAD_CANCEL_DISABLE;
	      ptw32_mcs_lock_release (&stateLock);

	      ptw32_throw (PTW32_EPS_CANCEL);
	    }

	  ptw32_mcs_lock_release (&stateLock);
	  return ESRCH;
	}
      else if (status != WAIT_TIMEOUT)
	{
	  return EINVAL;
	}
    }
  else
    {
      Sleep (wait_time);
    }

  return (0);
}