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
typedef  int /*<<< orphan*/ * QueueHandle_t ;
typedef  int /*<<< orphan*/  OsiReturnVal_e ;
typedef  scalar_t__ OsiMsgQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/ * xQueueCreate (unsigned long,unsigned long) ; 

OsiReturnVal_e osi_MsgQCreate(OsiMsgQ_t* 		pMsgQ , 
			      char*			pMsgQName,
			      unsigned long 		MsgSize,
			      unsigned long		MaxMsgs)
{
	QueueHandle_t handle;

	//Create Queue
	handle = xQueueCreate( MaxMsgs, MsgSize );
	ASSERT (handle != NULL);

	*pMsgQ = (OsiMsgQ_t)handle;
	return OSI_OK;
}