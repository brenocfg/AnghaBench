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
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
typedef  int /*<<< orphan*/  dwc_ep_t ;

/* Variables and functions */

__attribute__((used)) static inline void print_memory_payload(dwc_otg_pcd_t * pcd,  dwc_ep_t * ep)
{
#ifdef DEBUG
	deptsiz_data_t deptsiz_init = {.d32 = 0 };
	deptsiz_data_t deptsiz_updt = {.d32 = 0 };
	int pack_num;
	unsigned payload;

	deptsiz_init.d32 = pcd->core_if->start_doeptsiz_val[ep->num];
	deptsiz_updt.d32 =
		DWC_READ_REG32(&pcd->core_if->dev_if->
						out_ep_regs[ep->num]->doeptsiz);
	/* Payload will be */
	payload = deptsiz_init.b.xfersize - deptsiz_updt.b.xfersize;
	/* Packet count is decremented every time a packet
	 * is written to the RxFIFO not in to the external memory
	 * So, if payload == 0, then it means no packet was sent to ext memory*/
	pack_num = (!payload) ? 0 : (deptsiz_init.b.pktcnt - deptsiz_updt.b.pktcnt);
	DWC_DEBUGPL(DBG_PCDV,
		"Payload for EP%d-%s\n",
		ep->num, (ep->is_in ? "IN" : "OUT"));
	DWC_DEBUGPL(DBG_PCDV,
		"Number of transfered bytes = 0x%08x\n", payload);
	DWC_DEBUGPL(DBG_PCDV,
		"Number of transfered packets = %d\n", pack_num);
#endif
}