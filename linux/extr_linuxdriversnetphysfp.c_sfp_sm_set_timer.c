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
struct sfp {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void sfp_sm_set_timer(struct sfp *sfp, unsigned int timeout)
{
	if (timeout)
		mod_delayed_work(system_power_efficient_wq, &sfp->timeout,
				 timeout);
	else
		cancel_delayed_work(&sfp->timeout);
}