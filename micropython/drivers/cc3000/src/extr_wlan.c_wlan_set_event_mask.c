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
struct TYPE_2__ {int InformHostOnTxComplete; int /*<<< orphan*/ * pucTxCommandBuffer; } ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFAIL ; 
 int /*<<< orphan*/  HCI_CMND_EVENT_MASK ; 
 int HCI_EVNT_WLAN_TX_COMPLETE ; 
 int HCI_EVNT_WLAN_UNSOL_BASE ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UINT32_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WLAN_SET_MASK_PARAMS_LEN ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 wlan_set_event_mask(UINT32 ulMask)
{
	INT32 ret;
	UINT8 *ptr;
	UINT8 *args;


	if ((ulMask & HCI_EVNT_WLAN_TX_COMPLETE) == HCI_EVNT_WLAN_TX_COMPLETE)
	{
		tSLInformation.InformHostOnTxComplete = 0;

		// Since an event is a virtual event - i.e. it is not coming from CC3000
		// there is no need to send anything to the device if it was an only event
		if (ulMask == HCI_EVNT_WLAN_TX_COMPLETE)
		{
			return 0;
		}

		ulMask &= ~HCI_EVNT_WLAN_TX_COMPLETE;
		ulMask |= HCI_EVNT_WLAN_UNSOL_BASE;
	}
	else
	{
		tSLInformation.InformHostOnTxComplete = 1;
	}

	ret = EFAIL;
	ptr = tSLInformation.pucTxCommandBuffer;
	args = (UINT8 *)(ptr + HEADERS_SIZE_CMD);

	// Fill in HCI packet structure
	args = UINT32_TO_STREAM(args, ulMask);

	// Initiate a HCI command
	hci_command_send(HCI_CMND_EVENT_MASK,
		ptr, WLAN_SET_MASK_PARAMS_LEN);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_CMND_EVENT_MASK, &ret);

	return(ret);
}