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
struct hw {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLLCTL ; 
 int /*<<< orphan*/  TRNCTL ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 

__attribute__((used)) static int hw_card_stop(struct hw *hw)
{
	unsigned int data;

	/* disable transport bus master and queueing of request */
	hw_write_20kx(hw, TRNCTL, 0x00);

	/* disable pll */
	data = hw_read_20kx(hw, PLLCTL);
	hw_write_20kx(hw, PLLCTL, (data & (~(0x0F<<12))));

	/* TODO: Disable interrupt and so on... */
	if (hw->irq >= 0)
		synchronize_irq(hw->irq);
	return 0;
}