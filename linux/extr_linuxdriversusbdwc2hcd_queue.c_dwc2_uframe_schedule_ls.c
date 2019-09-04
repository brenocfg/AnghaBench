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
struct dwc2_qh {scalar_t__ host_us; scalar_t__ device_us; scalar_t__ host_interval; scalar_t__ device_interval; int /*<<< orphan*/  schedule_low_speed; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dwc2_ls_pmap_schedule (struct dwc2_hsotg*,struct dwc2_qh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_uframe_schedule_ls(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	/* In non-split host and device time are the same */
	WARN_ON(qh->host_us != qh->device_us);
	WARN_ON(qh->host_interval != qh->device_interval);
	WARN_ON(!qh->schedule_low_speed);

	/* Run on the main low speed schedule (no split = no hub = no TT) */
	return dwc2_ls_pmap_schedule(hsotg, qh, 0);
}