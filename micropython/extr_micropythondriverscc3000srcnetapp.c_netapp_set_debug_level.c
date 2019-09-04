#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;
typedef  int /*<<< orphan*/  INT8 ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFAIL ; 
 int /*<<< orphan*/  HCI_NETAPP_SET_DEBUG_LEVEL ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  NETAPP_SET_DEBUG_LEVEL_PARAMS_LEN ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UINT32_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 netapp_set_debug_level(UINT32 ulLevel)
{
	INT8 scRet;    
	UINT8 *ptr, *args;

	scRet = EFAIL;
	ptr = tSLInformation.pucTxCommandBuffer;
	args = (ptr + HEADERS_SIZE_CMD);

	//
	// Fill in temporary command buffer
	//
	args = UINT32_TO_STREAM(args, ulLevel);


	//
	// Initiate a HCI command
	//
	hci_command_send(HCI_NETAPP_SET_DEBUG_LEVEL, ptr, NETAPP_SET_DEBUG_LEVEL_PARAMS_LEN);

	//
	// Wait for command complete event
	//
	SimpleLinkWaitEvent(HCI_NETAPP_SET_DEBUG_LEVEL, &scRet);

	return(scRet);

}