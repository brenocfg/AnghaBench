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
struct ci_hdrc {scalar_t__ vbus_active; scalar_t__ is_otg; } ;

/* Variables and functions */
 int OTGSC_BSVIE ; 
 int OTGSC_BSVIS ; 
 int /*<<< orphan*/  hw_write_otgsc (struct ci_hdrc*,int,int) ; 

__attribute__((used)) static void udc_id_switch_for_host(struct ci_hdrc *ci)
{
	/*
	 * host doesn't care B_SESSION_VALID event
	 * so clear and disbale BSV irq
	 */
	if (ci->is_otg)
		hw_write_otgsc(ci, OTGSC_BSVIE | OTGSC_BSVIS, OTGSC_BSVIS);

	ci->vbus_active = 0;
}