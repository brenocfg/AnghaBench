#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ x; scalar_t__ p; } ;
struct TYPE_8__ {struct TYPE_8__* prevReuse; int /*<<< orphan*/  state; TYPE_2__ ptHandle; } ;
typedef  TYPE_1__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  TYPE_2__ pthread_t ;

/* Variables and functions */
 scalar_t__ PTW32_THREAD_ID_REUSE_INCREMENT ; 
 TYPE_1__* PTW32_THREAD_REUSE_EMPTY ; 
 int /*<<< orphan*/  PThreadStateReuse ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 TYPE_1__* ptw32_threadReuseBottom ; 
 TYPE_1__* ptw32_threadReuseTop ; 
 int /*<<< orphan*/  ptw32_thread_reuse_lock ; 

void
ptw32_threadReusePush (pthread_t thread)
{
  ptw32_thread_t * tp = (ptw32_thread_t *) thread.p;
  pthread_t t;
  ptw32_mcs_local_node_t node;

  ptw32_mcs_lock_acquire(&ptw32_thread_reuse_lock, &node);

  t = tp->ptHandle;
  memset(tp, 0, sizeof(ptw32_thread_t));

  /* Must restore the original POSIX handle that we just wiped. */
  tp->ptHandle = t;

  /* Bump the reuse counter now */
#if defined(PTW32_THREAD_ID_REUSE_INCREMENT)
  tp->ptHandle.x += PTW32_THREAD_ID_REUSE_INCREMENT;
#else
  tp->ptHandle.x++;
#endif

  tp->state = PThreadStateReuse;

  tp->prevReuse = PTW32_THREAD_REUSE_EMPTY;

  if (PTW32_THREAD_REUSE_EMPTY != ptw32_threadReuseBottom)
    {
      ptw32_threadReuseBottom->prevReuse = tp;
    }
  else
    {
      ptw32_threadReuseTop = tp;
    }

  ptw32_threadReuseBottom = tp;

  ptw32_mcs_lock_release(&node);
}