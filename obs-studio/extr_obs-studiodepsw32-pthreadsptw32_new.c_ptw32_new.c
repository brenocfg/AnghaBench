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
struct TYPE_8__ {scalar_t__ x; TYPE_1__* p; } ;
struct TYPE_6__ {TYPE_3__ ptHandle; int /*<<< orphan*/ * cancelEvent; int /*<<< orphan*/ * robustMxList; scalar_t__ robustMxListLock; scalar_t__ threadLock; scalar_t__ stateLock; int /*<<< orphan*/  cancelType; int /*<<< orphan*/  cancelState; int /*<<< orphan*/  detachState; int /*<<< orphan*/  sched_priority; scalar_t__ seqNumber; } ;
typedef  TYPE_1__ ptw32_thread_t ;
struct TYPE_7__ {scalar_t__ x; TYPE_1__* p; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_DEFERRED ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 scalar_t__ PTW32_FALSE ; 
 scalar_t__ PTW32_TRUE ; 
 int /*<<< orphan*/  THREAD_PRIORITY_NORMAL ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__ ptw32_threadReusePop () ; 
 int /*<<< orphan*/  ptw32_threadReusePush (TYPE_3__) ; 
 scalar_t__ ptw32_threadSeqNumber ; 

pthread_t
ptw32_new (void)
{
  pthread_t t;
  pthread_t nil = {NULL, 0};
  ptw32_thread_t * tp;

  /*
   * If there's a reusable pthread_t then use it.
   */
  t = ptw32_threadReusePop ();

  if (NULL != t.p)
    {
      tp = (ptw32_thread_t *) t.p;
    }
  else
    {
      /* No reuse threads available */
      tp = (ptw32_thread_t *) calloc (1, sizeof(ptw32_thread_t));

      if (tp == NULL)
	{
	  return nil;
	}

      /* ptHandle.p needs to point to it's parent ptw32_thread_t. */
      t.p = tp->ptHandle.p = tp;
      t.x = tp->ptHandle.x = 0;
    }

  /* Set default state. */
  tp->seqNumber = ++ptw32_threadSeqNumber;
  tp->sched_priority = THREAD_PRIORITY_NORMAL;
  tp->detachState = PTHREAD_CREATE_JOINABLE;
  tp->cancelState = PTHREAD_CANCEL_ENABLE;
  tp->cancelType = PTHREAD_CANCEL_DEFERRED;
  tp->stateLock = 0;
  tp->threadLock = 0;
  tp->robustMxListLock = 0;
  tp->robustMxList = NULL;
  tp->cancelEvent = CreateEvent (0, (int) PTW32_TRUE,	/* manualReset  */
				 (int) PTW32_FALSE,	/* setSignaled  */
				 NULL);

  if (tp->cancelEvent == NULL)
    {
      ptw32_threadReusePush (tp->ptHandle);
      return nil;
    }

  return t;

}