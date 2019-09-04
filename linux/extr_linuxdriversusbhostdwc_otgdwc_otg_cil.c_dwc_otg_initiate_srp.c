#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int sesreq; } ;
struct TYPE_9__ {void* d32; TYPE_2__ b; } ;
typedef  TYPE_3__ gotgctl_data_t ;
struct TYPE_10__ {TYPE_1__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  gotgctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_INFO (char*) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dwc_otg_pcd_start_srp_timer (TYPE_4__*) ; 

void dwc_otg_initiate_srp(dwc_otg_core_if_t * core_if)
{
	uint32_t *addr = (uint32_t *) & (core_if->core_global_regs->gotgctl);
	gotgctl_data_t mem;
	gotgctl_data_t val;

	val.d32 = DWC_READ_REG32(addr);
	if (val.b.sesreq) {
		DWC_ERROR("Session Request Already active!\n");
		return;
	}

	DWC_INFO("Session Request Initated\n");	//NOTICE
	mem.d32 = DWC_READ_REG32(addr);
	mem.b.sesreq = 1;
	DWC_WRITE_REG32(addr, mem.d32);

	/* Start the SRP timer */
	dwc_otg_pcd_start_srp_timer(core_if);
	return;
}