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
struct hw {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GCTL ; 
 int /*<<< orphan*/  GCTL_AID ; 
 int /*<<< orphan*/  GCTL_EAI ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_field (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  set_field (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_auto_init(struct hw *hw)
{
	unsigned int gctl;
	int i;

	gctl = hw_read_20kx(hw, GCTL);
	set_field(&gctl, GCTL_EAI, 0);
	hw_write_20kx(hw, GCTL, gctl);
	set_field(&gctl, GCTL_EAI, 1);
	hw_write_20kx(hw, GCTL, gctl);
	mdelay(10);
	for (i = 0; i < 400000; i++) {
		gctl = hw_read_20kx(hw, GCTL);
		if (get_field(gctl, GCTL_AID))
			break;
	}
	if (!get_field(gctl, GCTL_AID)) {
		dev_alert(hw->card->dev, "Card Auto-init failed!!!\n");
		return -EBUSY;
	}

	return 0;
}