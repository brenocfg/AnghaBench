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
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CMND_READ_SP_VERSION ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

UINT8 nvmem_read_sp_version(UINT8* patchVer)
{
	UINT8 *ptr;
	// 1st byte is the status and the rest is the SP version
	UINT8	retBuf[5];	

	ptr = tSLInformation.pucTxCommandBuffer;

	// Initiate a HCI command, no args are required
	hci_command_send(HCI_CMND_READ_SP_VERSION, ptr, 0);	
	SimpleLinkWaitEvent(HCI_CMND_READ_SP_VERSION, retBuf);

	// package ID
	*patchVer = retBuf[3];			
	// package build number
	*(patchVer+1) = retBuf[4];		

	return(retBuf[0]);
}