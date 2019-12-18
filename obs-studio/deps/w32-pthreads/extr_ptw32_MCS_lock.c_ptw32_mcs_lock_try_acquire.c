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
typedef  int /*<<< orphan*/  ptw32_mcs_lock_t ;
struct TYPE_3__ {scalar_t__ next; scalar_t__ readyFlag; scalar_t__ nextFlag; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ ptw32_mcs_local_node_t ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_PVOID_PTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_PVOID ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int 
ptw32_mcs_lock_try_acquire (ptw32_mcs_lock_t * lock, ptw32_mcs_local_node_t * node)
{
  node->lock = lock;
  node->nextFlag = 0;
  node->readyFlag = 0;
  node->next = 0; /* initially, no successor */

  return ((PTW32_INTERLOCKED_PVOID)PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR((PTW32_INTERLOCKED_PVOID_PTR)lock,
                                                        (PTW32_INTERLOCKED_PVOID)node,
                                                        (PTW32_INTERLOCKED_PVOID)0)
                                 == (PTW32_INTERLOCKED_PVOID)0) ? 0 : EBUSY;
}