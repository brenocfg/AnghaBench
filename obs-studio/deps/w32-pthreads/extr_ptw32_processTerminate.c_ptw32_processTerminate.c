#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* prevReuse; } ;
typedef  TYPE_1__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;

/* Variables and functions */
 scalar_t__ PTW32_FALSE ; 
 TYPE_1__* PTW32_THREAD_REUSE_EMPTY ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptw32_cleanupKey ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 scalar_t__ ptw32_processInitialized ; 
 int /*<<< orphan*/ * ptw32_selfThreadKey ; 
 TYPE_1__* ptw32_threadReuseTop ; 
 int /*<<< orphan*/  ptw32_thread_reuse_lock ; 

void
ptw32_processTerminate (void)
     /*
      * ------------------------------------------------------
      * DOCPRIVATE
      *      This function performs process wide termination for
      *      the pthread library.
      *
      * PARAMETERS
      *      N/A
      *
      * DESCRIPTION
      *      This function performs process wide termination for
      *      the pthread library.
      *      This routine sets the global variable
      *      ptw32_processInitialized to FALSE
      *
      * RESULTS
      *              N/A
      *
      * ------------------------------------------------------
      */
{
  if (ptw32_processInitialized)
    {
      ptw32_thread_t * tp, * tpNext;
      ptw32_mcs_local_node_t node;

      if (ptw32_selfThreadKey != NULL)
	{
	  /*
	   * Release ptw32_selfThreadKey
	   */
	  pthread_key_delete (ptw32_selfThreadKey);

	  ptw32_selfThreadKey = NULL;
	}

      if (ptw32_cleanupKey != NULL)
	{
	  /*
	   * Release ptw32_cleanupKey
	   */
	  pthread_key_delete (ptw32_cleanupKey);

	  ptw32_cleanupKey = NULL;
	}

      ptw32_mcs_lock_acquire(&ptw32_thread_reuse_lock, &node);

      tp = ptw32_threadReuseTop;
      while (tp != PTW32_THREAD_REUSE_EMPTY)
	{
	  tpNext = tp->prevReuse;
	  free (tp);
	  tp = tpNext;
	}

      ptw32_mcs_lock_release(&node);

      ptw32_processInitialized = PTW32_FALSE;
    }

}