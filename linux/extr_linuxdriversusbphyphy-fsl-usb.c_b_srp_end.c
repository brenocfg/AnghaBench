#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int b_srp_done; scalar_t__ b_sess_vld; } ;
struct TYPE_6__ {TYPE_1__* otg; } ;
struct TYPE_8__ {TYPE_3__ fsm; TYPE_2__ phy; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ OTG_STATE_B_SRP_INIT ; 
 TYPE_4__* fsl_otg_dev ; 
 int /*<<< orphan*/  fsl_otg_dischrg_vbus (int /*<<< orphan*/ ) ; 
 int srp_wait_done ; 

void b_srp_end(unsigned long foo)
{
	fsl_otg_dischrg_vbus(0);
	srp_wait_done = 1;

	if ((fsl_otg_dev->phy.otg->state == OTG_STATE_B_SRP_INIT) &&
	    fsl_otg_dev->fsm.b_sess_vld)
		fsl_otg_dev->fsm.b_srp_done = 1;
}