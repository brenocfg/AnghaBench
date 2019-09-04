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
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CMND_WLAN_IOCTL_GET_SCAN_RESULTS ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UINT32_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_GET_SCAN_RESULTS_PARAMS_LEN ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 wlan_ioctl_get_scan_results(UINT32 ulScanTimeout,
	UINT8 *ucResults)
{
	UINT8 *ptr;
	UINT8 *args;

	ptr = tSLInformation.pucTxCommandBuffer;
	args = (ptr + HEADERS_SIZE_CMD);

	// Fill in temporary command buffer
	args = UINT32_TO_STREAM(args, ulScanTimeout);

	// Initiate a HCI command
	hci_command_send(HCI_CMND_WLAN_IOCTL_GET_SCAN_RESULTS,
		ptr, WLAN_GET_SCAN_RESULTS_PARAMS_LEN);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_CMND_WLAN_IOCTL_GET_SCAN_RESULTS, ucResults);

	return(0);
}