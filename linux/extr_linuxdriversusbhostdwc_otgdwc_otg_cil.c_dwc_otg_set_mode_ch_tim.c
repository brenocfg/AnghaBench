#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  modechtimen; } ;
struct TYPE_10__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_4__ hcfg_data_t ;
struct TYPE_11__ {TYPE_3__* host_if; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_9__ {TYPE_2__* host_global_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  hcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dwc_otg_set_mode_ch_tim(dwc_otg_core_if_t * core_if, uint32_t val)
{
	hcfg_data_t hcfg;
	hcfg.d32 = DWC_READ_REG32(&core_if->host_if->host_global_regs->hcfg);
	hcfg.b.modechtimen = val;
	DWC_WRITE_REG32(&core_if->host_if->host_global_regs->hcfg, hcfg.d32);
}