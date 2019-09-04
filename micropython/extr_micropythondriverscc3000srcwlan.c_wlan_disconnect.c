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
typedef  int /*<<< orphan*/  INT32 ;
typedef  int /*<<< orphan*/  CC3000_EXPORT ;

/* Variables and functions */
 int /*<<< orphan*/  EFAIL ; 
 int /*<<< orphan*/  HCI_CMND_WLAN_DISCONNECT ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

INT32 wlan_disconnect()
{
	INT32 ret;
	UINT8 *ptr;

	ret = EFAIL;
	ptr = tSLInformation.pucTxCommandBuffer;

	hci_command_send(HCI_CMND_WLAN_DISCONNECT, ptr, 0);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_CMND_WLAN_DISCONNECT, &ret);
	CC3000_EXPORT(errno) = ret;

	return(ret);
}