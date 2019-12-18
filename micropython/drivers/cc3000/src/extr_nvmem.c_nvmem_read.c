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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {int* pucTxCommandBuffer; } ;
typedef  int INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CMND_NVMEM_READ ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  NVMEM_READ_PARAMS_LEN ; 
 int /*<<< orphan*/  SimpleLinkWaitData (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int*) ; 
 int* UINT32_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 nvmem_read(UINT32 ulFileId, UINT32 ulLength, UINT32 ulOffset, UINT8 *buff)
{
	UINT8 ucStatus = 0xFF;
	UINT8 *ptr;
	UINT8 *args;

	ptr = tSLInformation.pucTxCommandBuffer;
	args = (ptr + HEADERS_SIZE_CMD);

	// Fill in HCI packet structure
	args = UINT32_TO_STREAM(args, ulFileId);
	args = UINT32_TO_STREAM(args, ulLength);
	args = UINT32_TO_STREAM(args, ulOffset);

	// Initiate a HCI command
	hci_command_send(HCI_CMND_NVMEM_READ, ptr, NVMEM_READ_PARAMS_LEN);
	SimpleLinkWaitEvent(HCI_CMND_NVMEM_READ, &ucStatus);

	// In case there is data - read it - even if an error code is returned
	// Note: It is the user responsibility to ignore the data in case of an error code

	// Wait for the data in a synchronous way. Here we assume that the buffer is 
	// big enough to store also parameters of nvmem

	SimpleLinkWaitData(buff, 0, 0);

	return(ucStatus);
}