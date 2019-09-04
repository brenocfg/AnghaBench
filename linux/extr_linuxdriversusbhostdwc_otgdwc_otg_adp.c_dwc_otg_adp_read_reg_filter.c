#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;
struct TYPE_3__ {scalar_t__ adp_tmout_int; scalar_t__ adp_prb_int; } ;
struct TYPE_4__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_2__ adpctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_adp_read_reg (int /*<<< orphan*/ *) ; 

uint32_t dwc_otg_adp_read_reg_filter(dwc_otg_core_if_t * core_if)
{
	adpctl_data_t adpctl;

	adpctl.d32 = dwc_otg_adp_read_reg(core_if);
	adpctl.b.adp_tmout_int = 0;
	adpctl.b.adp_prb_int = 0;
	adpctl.b.adp_tmout_int = 0;

	return adpctl.d32;
}