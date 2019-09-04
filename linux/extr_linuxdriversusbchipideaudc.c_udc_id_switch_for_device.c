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
struct ci_hdrc {scalar_t__ is_otg; } ;

/* Variables and functions */
 int OTGSC_BSVIE ; 
 int OTGSC_BSVIS ; 
 int /*<<< orphan*/  hw_write_otgsc (struct ci_hdrc*,int,int) ; 

__attribute__((used)) static int udc_id_switch_for_device(struct ci_hdrc *ci)
{
	if (ci->is_otg)
		/* Clear and enable BSV irq */
		hw_write_otgsc(ci, OTGSC_BSVIS | OTGSC_BSVIE,
					OTGSC_BSVIS | OTGSC_BSVIE);

	return 0;
}