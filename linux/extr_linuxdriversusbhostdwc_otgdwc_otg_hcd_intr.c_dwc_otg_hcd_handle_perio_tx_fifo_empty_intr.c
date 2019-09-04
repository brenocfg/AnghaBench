#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_OTG_TRANSACTION_PERIODIC ; 
 int /*<<< orphan*/  dwc_otg_hcd_queue_transactions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t dwc_otg_hcd_handle_perio_tx_fifo_empty_intr(dwc_otg_hcd_t * dwc_otg_hcd)
{
	DWC_DEBUGPL(DBG_HCD, "--Periodic TxFIFO Empty Interrupt--\n");
	dwc_otg_hcd_queue_transactions(dwc_otg_hcd,
				       DWC_OTG_TRANSACTION_PERIODIC);
	return 1;
}