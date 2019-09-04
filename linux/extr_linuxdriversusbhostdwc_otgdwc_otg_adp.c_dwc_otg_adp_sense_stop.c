#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {scalar_t__ sense_enabled; } ;
struct TYPE_10__ {TYPE_1__ adp; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_9__ {int adp_sns_int; scalar_t__ enasns; } ;
struct TYPE_11__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_4__ adpctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_adp_read_reg_filter (TYPE_3__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_write_reg (TYPE_3__*,int /*<<< orphan*/ ) ; 

uint32_t dwc_otg_adp_sense_stop(dwc_otg_core_if_t * core_if)
{
	adpctl_data_t adpctl;

	core_if->adp.sense_enabled = 0;

	adpctl.d32 = dwc_otg_adp_read_reg_filter(core_if);
	adpctl.b.enasns = 0;
	adpctl.b.adp_sns_int = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);

	return 0;
}