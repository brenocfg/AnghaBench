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
struct adf7242_local {int /*<<< orphan*/  work; int /*<<< orphan*/  wqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RC_RX ; 
 int /*<<< orphan*/  RC_STATUS_MASK ; 
 int /*<<< orphan*/  RC_STATUS_PHY_RDY ; 
 int /*<<< orphan*/  adf7242_clear_irqstat (struct adf7242_local*) ; 
 int adf7242_cmd (struct adf7242_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf7242_wait_status (struct adf7242_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static int adf7242_cmd_rx(struct adf7242_local *lp)
{
	/* Wait until the ACK is sent */
	adf7242_wait_status(lp, RC_STATUS_PHY_RDY, RC_STATUS_MASK, __LINE__);
	adf7242_clear_irqstat(lp);
	mod_delayed_work(lp->wqueue, &lp->work, msecs_to_jiffies(400));

	return adf7242_cmd(lp, CMD_RC_RX);
}