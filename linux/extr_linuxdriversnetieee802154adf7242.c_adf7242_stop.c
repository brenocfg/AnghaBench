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
struct ieee802154_hw {struct adf7242_local* priv; } ;
struct adf7242_local {int /*<<< orphan*/  flags; int /*<<< orphan*/  work; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RC_IDLE ; 
 int /*<<< orphan*/  FLAG_START ; 
 int /*<<< orphan*/  adf7242_clear_irqstat (struct adf7242_local*) ; 
 int /*<<< orphan*/  adf7242_cmd (struct adf7242_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adf7242_stop(struct ieee802154_hw *hw)
{
	struct adf7242_local *lp = hw->priv;

	disable_irq(lp->spi->irq);
	cancel_delayed_work_sync(&lp->work);
	adf7242_cmd(lp, CMD_RC_IDLE);
	clear_bit(FLAG_START, &lp->flags);
	adf7242_clear_irqstat(lp);
}