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
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;
typedef  int INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  HCI_CMND_WLAN_IOCTL_SET_SCANPARAM ; 
 int HEADERS_SIZE_CMD ; 
 int SL_SET_SCAN_PARAMS_INTERVAL_LIST_SIZE ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * UINT32_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WLAN_SET_SCAN_PARAMS_LEN ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 wlan_ioctl_set_scan_params(UINT32 uiEnable, UINT32 uiMinDwellTime,
	UINT32 uiMaxDwellTime,
	UINT32 uiNumOfProbeRequests,
	UINT32 uiChannelMask,INT32 iRSSIThreshold,
	UINT32 uiSNRThreshold,
	UINT32 uiDefaultTxPower,
	UINT32 *aiIntervalList)
{
	UINT32  uiRes;
	UINT8 *ptr;
	UINT8 *args;

	ptr = tSLInformation.pucTxCommandBuffer;
	args = (ptr + HEADERS_SIZE_CMD);

	// Fill in temporary command buffer
	args = UINT32_TO_STREAM(args, 36);
	args = UINT32_TO_STREAM(args, uiEnable);
	args = UINT32_TO_STREAM(args, uiMinDwellTime);
	args = UINT32_TO_STREAM(args, uiMaxDwellTime);
	args = UINT32_TO_STREAM(args, uiNumOfProbeRequests);
	args = UINT32_TO_STREAM(args, uiChannelMask);
	args = UINT32_TO_STREAM(args, iRSSIThreshold);
	args = UINT32_TO_STREAM(args, uiSNRThreshold);
	args = UINT32_TO_STREAM(args, uiDefaultTxPower);
	ARRAY_TO_STREAM(args, aiIntervalList, sizeof(UINT32) * 
		SL_SET_SCAN_PARAMS_INTERVAL_LIST_SIZE);

	// Initiate a HCI command
	hci_command_send(HCI_CMND_WLAN_IOCTL_SET_SCANPARAM,
		ptr, WLAN_SET_SCAN_PARAMS_LEN);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_CMND_WLAN_IOCTL_SET_SCANPARAM, &uiRes);

	return(uiRes);
}