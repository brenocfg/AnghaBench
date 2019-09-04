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
typedef  scalar_t__ u32 ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_CONTROLLER_PHY_START_TIMEOUT ; 
 int SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL ; 
 scalar_t__ SCIC_SDS_SIGNATURE_FIS_TIMEOUT ; 
 int SCI_MAX_PHYS ; 

__attribute__((used)) static u32 sci_controller_get_suggested_start_timeout(struct isci_host *ihost)
{
	/* Validate the user supplied parameters. */
	if (!ihost)
		return 0;

	/*
	 * The suggested minimum timeout value for a controller start operation:
	 *
	 *     Signature FIS Timeout
	 *   + Phy Start Timeout
	 *   + Number of Phy Spin Up Intervals
	 *   ---------------------------------
	 *   Number of milliseconds for the controller start operation.
	 *
	 * NOTE: The number of phy spin up intervals will be equivalent
	 *       to the number of phys divided by the number phys allowed
	 *       per interval - 1 (once OEM parameters are supported).
	 *       Currently we assume only 1 phy per interval. */

	return SCIC_SDS_SIGNATURE_FIS_TIMEOUT
		+ SCIC_SDS_CONTROLLER_PHY_START_TIMEOUT
		+ ((SCI_MAX_PHYS - 1) * SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL);
}