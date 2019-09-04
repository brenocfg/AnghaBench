#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ci_hdrc {int is_otg; int /*<<< orphan*/  dev; TYPE_1__* platdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_DCCPARAMS ; 
 int CI_HDRC_DUAL_ROLE_NOT_OTG ; 
 int DCCPARAMS_DC ; 
 int DCCPARAMS_HC ; 
 int OTGSC_INT_EN_BITS ; 
 int OTGSC_INT_STATUS_BITS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_write_otgsc (struct ci_hdrc*,int,int) ; 

__attribute__((used)) static void ci_get_otg_capable(struct ci_hdrc *ci)
{
	if (ci->platdata->flags & CI_HDRC_DUAL_ROLE_NOT_OTG)
		ci->is_otg = false;
	else
		ci->is_otg = (hw_read(ci, CAP_DCCPARAMS,
				DCCPARAMS_DC | DCCPARAMS_HC)
					== (DCCPARAMS_DC | DCCPARAMS_HC));
	if (ci->is_otg) {
		dev_dbg(ci->dev, "It is OTG capable controller\n");
		/* Disable and clear all OTG irq */
		hw_write_otgsc(ci, OTGSC_INT_EN_BITS | OTGSC_INT_STATUS_BITS,
							OTGSC_INT_STATUS_BITS);
	}
}