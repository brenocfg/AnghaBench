#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ word; } ;
struct TYPE_10__ {TYPE_2__ counter; } ;
typedef  TYPE_3__ ptw32_oll_snziRoot_t ;
struct TYPE_11__ {TYPE_3__ proxyRoot; } ;
typedef  TYPE_4__ ptw32_oll_csnzi_t ;
struct TYPE_8__ {scalar_t__ word; } ;
struct TYPE_12__ {TYPE_1__ counter; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_SIZEPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_SIZE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PTW32_FALSE ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PTW32_TRUE ; 
 TYPE_3__ ptw32_oll_snziRoot_closedAndZero ; 
 TYPE_5__ ptw32_oll_snziRoot_openAndZero ; 

BOOL
ptw32_oll_CloseIfEmpty(ptw32_oll_csnzi_t* csnziPtr)
{
  ptw32_oll_snziRoot_t newProxy, oldProxy;
  do
  {
    oldProxy = csnziPtr->proxyRoot;
    if (oldProxy.counter.word != ptw32_oll_snziRoot_openAndZero.counter.word)
    {
      return PTW32_FALSE;
    }
    newProxy = ptw32_oll_snziRoot_closedAndZero;
  } while (PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE(
                 (PTW32_INTERLOCKED_SIZEPTR)&csnziPtr->proxyRoot.counter,
                 (PTW32_INTERLOCKED_SIZE)newProxy.counter.word,
                 (PTW32_INTERLOCKED_SIZE)oldProxy.counter.word)
           != (PTW32_INTERLOCKED_SIZE)oldProxy.counter.word);
  return PTW32_TRUE;
}