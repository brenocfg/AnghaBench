#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  QueueHandle_t ;
typedef  int /*<<< orphan*/  OsiTime_t ;
typedef  int /*<<< orphan*/  OsiReturnVal_e ;
typedef  scalar_t__ OsiMsgQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/  OSI_OPERATION_FAILED ; 
 int /*<<< orphan*/  pdFALSE ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  taskYIELD () ; 
 int /*<<< orphan*/  xHigherPriorityTaskWoken ; 
 scalar_t__ xQueueSendFromISR (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

OsiReturnVal_e osi_MsgQWrite(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout)
{
	xHigherPriorityTaskWoken = pdFALSE;
    if(pdPASS == xQueueSendFromISR((QueueHandle_t) *pMsgQ, pMsg, &xHigherPriorityTaskWoken ))
    {
		taskYIELD ();
		return OSI_OK;
    }
	else
	{
		return OSI_OPERATION_FAILED;
	}
}