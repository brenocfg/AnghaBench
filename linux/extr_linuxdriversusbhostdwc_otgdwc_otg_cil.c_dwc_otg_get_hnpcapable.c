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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  hnpcap; } ;
struct TYPE_8__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_3__ gusbcfg_data_t ;
struct TYPE_9__ {TYPE_1__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_6__ {int /*<<< orphan*/  gusbcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

uint32_t dwc_otg_get_hnpcapable(dwc_otg_core_if_t * core_if)
{
	gusbcfg_data_t usbcfg;
	usbcfg.d32 = DWC_READ_REG32(&core_if->core_global_regs->gusbcfg);
	return usbcfg.b.hnpcap;
}