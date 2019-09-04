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
struct TYPE_2__ {int usRxDataPending; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_event_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ tSLInformation ; 

void SimpleLinkWaitData(UINT8 *pBuf, UINT8 *from, UINT8 *fromlen)
{
	// In the blocking implementation the control to caller will be returned only 
	// after the end of current transaction, i.e. only after data will be received
	tSLInformation.usRxDataPending = 1;
	hci_event_handler(pBuf, from, fromlen);
}