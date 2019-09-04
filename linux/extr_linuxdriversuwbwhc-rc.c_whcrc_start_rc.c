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
struct whcrc {scalar_t__ rc_base; TYPE_1__* umc_dev; } ;
struct uwb_rc {struct whcrc* priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 scalar_t__ URCCMD ; 
 int /*<<< orphan*/  URCCMD_RESET ; 
 int /*<<< orphan*/  URCCMD_RS ; 
 scalar_t__ URCINTR ; 
 int /*<<< orphan*/  URCINTR_EN_ALL ; 
 scalar_t__ URCSTS ; 
 int /*<<< orphan*/  URCSTS_HALTED ; 
 int /*<<< orphan*/  le_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ whci_wait_for (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  whcrc_enable_events (struct whcrc*) ; 

__attribute__((used)) static int whcrc_start_rc(struct uwb_rc *rc)
{
	struct whcrc *whcrc = rc->priv;
	struct device *dev = &whcrc->umc_dev->dev;

	/* Reset the thing */
	le_writel(URCCMD_RESET, whcrc->rc_base + URCCMD);
	if (whci_wait_for(dev, whcrc->rc_base + URCCMD, URCCMD_RESET, 0,
			  5000, "hardware reset") < 0)
		return -EBUSY;

	/* Set the event buffer, start the controller (enable IRQs later) */
	le_writel(0, whcrc->rc_base + URCINTR);
	le_writel(URCCMD_RS, whcrc->rc_base + URCCMD);
	if (whci_wait_for(dev, whcrc->rc_base + URCSTS, URCSTS_HALTED, 0,
			  5000, "radio controller start") < 0)
		return -ETIMEDOUT;
	whcrc_enable_events(whcrc);
	le_writel(URCINTR_EN_ALL, whcrc->rc_base + URCINTR);
	return 0;
}