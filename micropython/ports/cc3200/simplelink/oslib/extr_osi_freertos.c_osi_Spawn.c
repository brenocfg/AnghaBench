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
struct TYPE_3__ {void* pValue; int /*<<< orphan*/  pEntry; } ;
typedef  TYPE_1__ tSimpleLinkSpawnMsg ;
typedef  int /*<<< orphan*/  P_OSI_SPAWN_ENTRY ;
typedef  int /*<<< orphan*/  OsiReturnVal_e ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/  OSI_OPERATION_FAILED ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  taskYIELD () ; 
 scalar_t__ xHigherPriorityTaskWoken ; 
 scalar_t__ xQueueSendFromISR (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  xSimpleLinkSpawnQueue ; 

OsiReturnVal_e osi_Spawn(P_OSI_SPAWN_ENTRY pEntry , void* pValue , unsigned long flags)
{

	tSimpleLinkSpawnMsg Msg;
	Msg.pEntry = pEntry;
	Msg.pValue = pValue;
	xHigherPriorityTaskWoken = pdFALSE;

	if(pdTRUE == xQueueSendFromISR( xSimpleLinkSpawnQueue, &Msg, &xHigherPriorityTaskWoken ))
	{
		if( xHigherPriorityTaskWoken )
		{
			taskYIELD ();
		}
		return OSI_OK;
	}
	return OSI_OPERATION_FAILED;
}