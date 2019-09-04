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
struct lola {int cold_reset; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR0 ; 
 int /*<<< orphan*/  BAR1 ; 
 int /*<<< orphan*/  BOARD_MODE ; 
 int EIO ; 
 int /*<<< orphan*/  GCTL ; 
 int /*<<< orphan*/  LOLA_GCTL_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned int lola_readl (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lola_writel (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int reset_controller(struct lola *chip)
{
	unsigned int gctl = lola_readl(chip, BAR0, GCTL);
	unsigned long end_time;

	if (gctl) {
		/* to be sure */
		lola_writel(chip, BAR1, BOARD_MODE, 0);
		return 0;
	}

	chip->cold_reset = 1;
	lola_writel(chip, BAR0, GCTL, LOLA_GCTL_RESET);
	end_time = jiffies + msecs_to_jiffies(200);
	do {
		msleep(1);
		gctl = lola_readl(chip, BAR0, GCTL);
		if (gctl)
			break;
	} while (time_before(jiffies, end_time));
	if (!gctl) {
		dev_err(chip->card->dev, "cannot reset controller\n");
		return -EIO;
	}
	return 0;
}