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
struct dwc2_qh {int /*<<< orphan*/  host_interval; struct dwc2_hs_transfer_time* hs_transfers; } ;
struct dwc2_hsotg {int /*<<< orphan*/  hs_periodic_bitmap; } ;
struct dwc2_hs_transfer_time {int start_schedule_us; int /*<<< orphan*/  duration_us; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_HS_PERIODIC_US_PER_UFRAME ; 
 int /*<<< orphan*/  DWC2_HS_SCHEDULE_UFRAMES ; 
 int pmap_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dwc2_hs_pmap_schedule(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh,
				 bool only_one_period, int index)
{
	struct dwc2_hs_transfer_time *trans_time = qh->hs_transfers + index;
	int us;

	us = pmap_schedule(hsotg->hs_periodic_bitmap,
			   DWC2_HS_PERIODIC_US_PER_UFRAME,
			   DWC2_HS_SCHEDULE_UFRAMES, trans_time->duration_us,
			   qh->host_interval, trans_time->start_schedule_us,
			   only_one_period);

	if (us < 0)
		return us;

	trans_time->start_schedule_us = us;
	return 0;
}