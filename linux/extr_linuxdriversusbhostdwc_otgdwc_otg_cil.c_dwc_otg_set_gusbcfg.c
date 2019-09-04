#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* core_global_regs; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int /*<<< orphan*/  gusbcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dwc_otg_set_gusbcfg(dwc_otg_core_if_t * core_if, uint32_t val)
{
	DWC_WRITE_REG32(&core_if->core_global_regs->gusbcfg, val);
}