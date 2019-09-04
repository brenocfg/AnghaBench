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
struct TYPE_9__ {TYPE_2__* tailPtr; } ;
typedef  TYPE_1__ ptw32_srwl_rwlock_t ;
struct TYPE_10__ {scalar_t__ kind; scalar_t__ spin; int /*<<< orphan*/  csnzi; struct TYPE_10__* qNextPtr; } ;
typedef  TYPE_2__ ptw32_srwl_node_t ;
struct TYPE_11__ {TYPE_2__* departFromPtr; void* ticket; } ;
typedef  TYPE_3__ ptw32_srwl_local_t ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_PVOIDPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_PVOID ;

/* Variables and functions */
 scalar_t__ PTW32_FALSE ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PTW32_TRUE ; 
 void* ptw32_oll_Arrive (int /*<<< orphan*/ ) ; 
 scalar_t__ ptw32_oll_Arrived (void*) ; 
 int /*<<< orphan*/  ptw32_oll_Open (int /*<<< orphan*/ ) ; 
 TYPE_2__* ptw32_srwl_AllocReaderNode (TYPE_3__*) ; 
 int /*<<< orphan*/  ptw32_srwl_FreeReaderNode (TYPE_2__*) ; 
 scalar_t__ ptw32_srwl_writer ; 

void
ptw32_srwl_ReaderLock(ptw32_srwl_rwlock_t* lockPtr, ptw32_srwl_local_t* localPtr)
{
  ptw32_srwl_node_t* rNodePtr = NULL;
  for (;;)
  {
    ptw32_srwl_node_t* tailPtr = lockPtr->tailPtr;
    /* If no nodes are in the queue */
    if (tailPtr == NULL)
    {
      if (rNodePtr == NULL)
      {
        rNodePtr = ptw32_srwl_AllocReaderNode(localPtr);
      }
      rNodePtr->spin = PTW32_FALSE;
      if (PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR(
                (PTW32_INTERLOCKED_PVOIDPTR)&lockPtr->tailPtr,
                (PTW32_INTERLOCKED_PVOID)rNodePtr,
                (PTW32_INTERLOCKED_PVOID)NULL)
          == (PTW32_INTERLOCKED_PVOID)rNodePtr)
      {
        ptw32_oll_Open(rNodePtr->csnzi);
        localPtr->ticket = ptw32_oll_Arrive(rNodePtr->csnzi);
        if (ptw32_oll_Arrived(localPtr->ticket))
        {
          localPtr->departFromPtr = rNodePtr;
          return;
        }
        /* Avoid reusing inserted node */
        rNodePtr = NULL;
      }
    }
    /* Otherwise, there is a node in the queue */
    else
    {
      /* Is last node a writer node? */
      if (tailPtr->kind == ptw32_srwl_writer)
      {
        if (rNodePtr == NULL)
        {
          rNodePtr = ptw32_srwl_AllocReaderNode(localPtr);
        }
        rNodePtr->spin = PTW32_TRUE;
        if (PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR(
                  (PTW32_INTERLOCKED_PVOIDPTR)&lockPtr->tailPtr,
                  (PTW32_INTERLOCKED_PVOID)rNodePtr,
                  (PTW32_INTERLOCKED_PVOID)tailPtr)
            == (PTW32_INTERLOCKED_PVOID)rNodePtr)
        {
          tailPtr->qNextPtr = rNodePtr;
          localPtr->ticket = ptw32_oll_Arrive(rNodePtr->csnzi);
          if (ptw32_oll_Arrived(localPtr->ticket))
          {
            localPtr->departFromPtr = rNodePtr;
            while (rNodePtr->spin);
            return;
          }
          /* Avoid reusing inserted node */
          rNodePtr = NULL;
        }
      }
      /*
       * Otherwise, last node is a reader node.
       * (tailPtr->kind == ptw32_srwl_reader)
       */
      else
      {
        localPtr->ticket = ptw32_oll_Arrive(tailPtr->csnzi);
        if (ptw32_oll_Arrived(localPtr->ticket))
        {
          if (rNodePtr != NULL)
          {
            ptw32_srwl_FreeReaderNode(rNodePtr);
          }
          localPtr->departFromPtr = tailPtr;
          while (tailPtr->spin);
          return;
        }
      }
    }
  }
}