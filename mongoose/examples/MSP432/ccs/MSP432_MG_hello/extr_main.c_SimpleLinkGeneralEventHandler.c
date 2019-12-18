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
struct TYPE_5__ {int /*<<< orphan*/  sender; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_1__ deviceEvent; } ;
struct TYPE_7__ {TYPE_2__ EventData; } ;
typedef  TYPE_3__ SlDeviceEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  LL_ERROR ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *e) {
  LOG(LL_ERROR, ("status %d sender %d", e->EventData.deviceEvent.status,
                 e->EventData.deviceEvent.sender));
}