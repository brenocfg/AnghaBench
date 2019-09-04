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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ath10k_htc {int /*<<< orphan*/  total_transmit_credits; } ;

/* Variables and functions */
 scalar_t__ ATH10K_HTC_SVC_ID_WMI_CONTROL ; 

__attribute__((used)) static u8 ath10k_htc_get_credit_allocation(struct ath10k_htc *htc,
					   u16 service_id)
{
	u8 allocation = 0;

	/* The WMI control service is the only service with flow control.
	 * Let it have all transmit credits.
	 */
	if (service_id == ATH10K_HTC_SVC_ID_WMI_CONTROL)
		allocation = htc->total_transmit_credits;

	return allocation;
}