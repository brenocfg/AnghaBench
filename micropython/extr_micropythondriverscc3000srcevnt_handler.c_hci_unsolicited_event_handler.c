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
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
struct TYPE_2__ {scalar_t__ usEventOrDataReceived; scalar_t__* pucReceivedData; } ;
typedef  int INT32 ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ HCI_TYPE_EVNT ; 
 int /*<<< orphan*/  SpiResumeSpi () ; 
 int hci_unsol_event_handler (int /*<<< orphan*/ *) ; 
 TYPE_1__ tSLInformation ; 

INT32 hci_unsolicited_event_handler(void)
{
	UINT32   res = 0;
	UINT8 *pucReceivedData;

	if (tSLInformation.usEventOrDataReceived != 0)
	{
		pucReceivedData = (tSLInformation.pucReceivedData);

		if (*pucReceivedData == HCI_TYPE_EVNT)
		{			

			// In case unsolicited event received - here the handling finished
			if (hci_unsol_event_handler((CHAR *)pucReceivedData) == 1)
			{

				// There was an unsolicited event received - we can release the buffer
				// and clean the event received 
				tSLInformation.usEventOrDataReceived = 0;

				res = 1;
				SpiResumeSpi();
			}
		}
	}

	return res;
}