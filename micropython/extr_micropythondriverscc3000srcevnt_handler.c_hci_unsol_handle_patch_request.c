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
typedef  scalar_t__ event_hdr ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {int* (* sDriverPatches ) (int /*<<< orphan*/ *) ;int* (* sFWPatches ) (int /*<<< orphan*/ *) ;int* (* sBootLoaderPatches ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  pucTxCommandBuffer; } ;
typedef  int CHAR ;

/* Variables and functions */
 scalar_t__ HCI_EVENT_HEADER_SIZE ; 
#define  HCI_EVENT_PATCHES_BOOTLOAD_REQ 130 
#define  HCI_EVENT_PATCHES_DRV_REQ 129 
#define  HCI_EVENT_PATCHES_FW_REQ 128 
 int /*<<< orphan*/  hci_patch_send (int const,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int* stub1 (int /*<<< orphan*/ *) ; 
 int* stub2 (int /*<<< orphan*/ *) ; 
 int* stub3 (int /*<<< orphan*/ *) ; 
 TYPE_1__ tSLInformation ; 

void hci_unsol_handle_patch_request(CHAR *event_hdr)
{
	CHAR *params = (CHAR *)(event_hdr) + HCI_EVENT_HEADER_SIZE;
	UINT32 ucLength = 0;
	CHAR *patch;

	switch (*params)
	{
	case HCI_EVENT_PATCHES_DRV_REQ:

		if (tSLInformation.sDriverPatches)
		{
			patch = tSLInformation.sDriverPatches(&ucLength);

			if (patch)
			{
				hci_patch_send(HCI_EVENT_PATCHES_DRV_REQ, 
					tSLInformation.pucTxCommandBuffer, patch, ucLength);
				return;
			}
		}

		// Send 0 length Patches response event
		hci_patch_send(HCI_EVENT_PATCHES_DRV_REQ, 
			tSLInformation.pucTxCommandBuffer, 0, 0);
		break;

	case HCI_EVENT_PATCHES_FW_REQ:

		if (tSLInformation.sFWPatches)
		{
			patch = tSLInformation.sFWPatches(&ucLength);

			// Build and send a patch
			if (patch)
			{
				hci_patch_send(HCI_EVENT_PATCHES_FW_REQ, 
					tSLInformation.pucTxCommandBuffer, patch, ucLength);
				return;
			}
		}

		// Send 0 length Patches response event
		hci_patch_send(HCI_EVENT_PATCHES_FW_REQ, 
			tSLInformation.pucTxCommandBuffer, 0, 0);
		break;

	case HCI_EVENT_PATCHES_BOOTLOAD_REQ:

		if (tSLInformation.sBootLoaderPatches)
		{
			patch = tSLInformation.sBootLoaderPatches(&ucLength);

			if (patch)
			{
				hci_patch_send(HCI_EVENT_PATCHES_BOOTLOAD_REQ,  
					tSLInformation.pucTxCommandBuffer, patch, ucLength);
				return;
			}
		}

		// Send 0 length Patches response event
		hci_patch_send(HCI_EVENT_PATCHES_BOOTLOAD_REQ, 
			tSLInformation.pucTxCommandBuffer, 0, 0);
		break;
	}
}