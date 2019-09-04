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
typedef  int /*<<< orphan*/  tNetappIpconfigRetArgs ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_NETAPP_IPCONFIG ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

void netapp_ipconfig( tNetappIpconfigRetArgs * ipconfig )
{
	UINT8 *ptr;

	ptr = tSLInformation.pucTxCommandBuffer;

	// Initiate a HCI command
	hci_command_send(HCI_NETAPP_IPCONFIG, ptr, 0);

	// Wait for command complete event
	SimpleLinkWaitEvent(HCI_NETAPP_IPCONFIG, ipconfig );

}