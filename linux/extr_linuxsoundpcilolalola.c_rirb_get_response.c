#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cmds; } ;
struct lola {int polling_mode; unsigned int res; unsigned int res_ex; TYPE_2__* card; int /*<<< orphan*/  last_extdata; int /*<<< orphan*/  last_data; int /*<<< orphan*/  last_verb; int /*<<< orphan*/  last_cmd_nid; TYPE_1__ rirb; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int LOLA_RIRB_EX_ERROR ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lola_update_rirb (struct lola*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verbose_debug (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int rirb_get_response(struct lola *chip, unsigned int *val,
			     unsigned int *extval)
{
	unsigned long timeout;

 again:
	timeout = jiffies + msecs_to_jiffies(1000);
	for (;;) {
		if (chip->polling_mode) {
			spin_lock_irq(&chip->reg_lock);
			lola_update_rirb(chip);
			spin_unlock_irq(&chip->reg_lock);
		}
		if (!chip->rirb.cmds) {
			*val = chip->res;
			if (extval)
				*extval = chip->res_ex;
			verbose_debug("get_response: %x, %x\n",
				      chip->res, chip->res_ex);
			if (chip->res_ex & LOLA_RIRB_EX_ERROR) {
				dev_warn(chip->card->dev, "RIRB ERROR: "
				       "NID=%x, verb=%x, data=%x, ext=%x\n",
				       chip->last_cmd_nid,
				       chip->last_verb, chip->last_data,
				       chip->last_extdata);
				return -EIO;
			}
			return 0;
		}
		if (time_after(jiffies, timeout))
			break;
		udelay(20);
		cond_resched();
	}
	dev_warn(chip->card->dev, "RIRB response error\n");
	if (!chip->polling_mode) {
		dev_warn(chip->card->dev, "switching to polling mode\n");
		chip->polling_mode = 1;
		goto again;
	}
	return -EIO;
}