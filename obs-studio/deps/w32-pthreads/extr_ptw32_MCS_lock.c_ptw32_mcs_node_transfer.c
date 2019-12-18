#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ next; scalar_t__ lock; scalar_t__ readyFlag; scalar_t__ nextFlag; } ;
typedef  TYPE_1__ ptw32_mcs_local_node_t ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_PVOID_PTR ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_PVOID ;

/* Variables and functions */
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_yield () ; 

void 
ptw32_mcs_node_transfer (ptw32_mcs_local_node_t * new_node, ptw32_mcs_local_node_t * old_node)
{
  new_node->lock = old_node->lock;
  new_node->nextFlag = 0; /* Not needed - used only in initial Acquire */
  new_node->readyFlag = 0; /* Not needed - we were waiting on this */
  new_node->next = 0;

  if ((ptw32_mcs_local_node_t *)PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR((PTW32_INTERLOCKED_PVOID_PTR)new_node->lock,
                                                                       (PTW32_INTERLOCKED_PVOID)new_node,
                                                                       (PTW32_INTERLOCKED_PVOID)old_node)
       != old_node)
    {
      /*
       * A successor has queued after us, so wait for them to link to us
       */
      while (old_node->next == 0)
        {
          sched_yield();
        }
      new_node->next = old_node->next;
    }
}