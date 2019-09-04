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
struct usb_hcd {int uses_new_polling; int /*<<< orphan*/  state; int /*<<< orphan*/  power_budget; } ;
struct max3421_hcd {int /*<<< orphan*/  ep_list; int /*<<< orphan*/  rh_state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX3421_RH_RUNNING ; 
 int /*<<< orphan*/  POWER_BUDGET ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
max3421_start(struct usb_hcd *hcd)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	spin_lock_init(&max3421_hcd->lock);
	max3421_hcd->rh_state = MAX3421_RH_RUNNING;

	INIT_LIST_HEAD(&max3421_hcd->ep_list);

	hcd->power_budget = POWER_BUDGET;
	hcd->state = HC_STATE_RUNNING;
	hcd->uses_new_polling = 1;
	return 0;
}