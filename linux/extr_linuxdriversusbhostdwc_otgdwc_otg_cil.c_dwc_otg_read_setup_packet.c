#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_8__ {scalar_t__ snpsid; TYPE_1__* core_global_regs; int /*<<< orphan*/ ** data_fifo; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  fn; int /*<<< orphan*/  pktsts; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  epnum; } ;
struct TYPE_9__ {TYPE_2__ b; void* d32; } ;
typedef  TYPE_4__ device_grxsts_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  grxstsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 

void dwc_otg_read_setup_packet(dwc_otg_core_if_t * core_if, uint32_t * dest)
{
	device_grxsts_data_t status;
	/* Get the 8 bytes of a setup transaction data */

	/* Pop 2 DWORDS off the receive data FIFO into memory */
	dest[0] = DWC_READ_REG32(core_if->data_fifo[0]);
	dest[1] = DWC_READ_REG32(core_if->data_fifo[0]);
	if (core_if->snpsid >= OTG_CORE_REV_3_00a) {
		status.d32 =
		    DWC_READ_REG32(&core_if->core_global_regs->grxstsp);
		DWC_DEBUGPL(DBG_ANY,
			    "EP:%d BCnt:%d " "pktsts:%x Frame:%d(0x%0x)\n",
			    status.b.epnum, status.b.bcnt, status.b.pktsts,
			    status.b.fn, status.b.fn);
	}
}