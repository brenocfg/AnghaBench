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
typedef  scalar_t__ UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/ * pucTxCommandBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CMND_SIMPLE_LINK_START ; 
 int HEADERS_SIZE_CMD ; 
 int /*<<< orphan*/  SL_PATCHES_REQUEST_DEFAULT ; 
 int /*<<< orphan*/  SL_PATCHES_REQUEST_FORCE_NONE ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_SL_INIT_START_PARAMS_LEN ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ tSLInformation ; 

__attribute__((used)) static void SimpleLink_Init_Start(UINT16 usPatchesAvailableAtHost)
{
	UINT8 *ptr;
	UINT8 *args;

	ptr = tSLInformation.pucTxCommandBuffer;
	args = (UINT8 *)(ptr + HEADERS_SIZE_CMD);

	UINT8_TO_STREAM(args, ((usPatchesAvailableAtHost) ? SL_PATCHES_REQUEST_FORCE_NONE : SL_PATCHES_REQUEST_DEFAULT));

	// IRQ Line asserted - send HCI_CMND_SIMPLE_LINK_START to CC3000
	hci_command_send(HCI_CMND_SIMPLE_LINK_START, ptr, WLAN_SL_INIT_START_PARAMS_LEN);

	SimpleLinkWaitEvent(HCI_CMND_SIMPLE_LINK_START, 0);
}