#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t count; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_1__ internal; } ;
struct TYPE_8__ {TYPE_2__ counter; } ;
struct TYPE_9__ {TYPE_3__ proxyRoot; } ;
typedef  TYPE_4__ ptw32_oll_csnzi_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ptw32_oll_snziRoot_closed ; 
 int /*<<< orphan*/  ptw32_oll_snziRoot_open ; 

void
ptw32_oll_OpenWithArrivals(ptw32_oll_csnzi_t* csnziPtr, size_t count, BOOL close)
{
  csnziPtr->proxyRoot.counter.internal.count = count;
  csnziPtr->proxyRoot.counter.internal.state = (close ? ptw32_oll_snziRoot_closed : ptw32_oll_snziRoot_open);
}