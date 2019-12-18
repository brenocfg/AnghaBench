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
struct hw {int /*<<< orphan*/  irq_callback_data; int /*<<< orphan*/  (* irq_callback ) (int /*<<< orphan*/ ,unsigned int) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t ct_20k1_interrupt(int irq, void *dev_id)
{
	struct hw *hw = dev_id;
	unsigned int status;

	status = hw_read_20kx(hw, GIP);
	if (!status)
		return IRQ_NONE;

	if (hw->irq_callback)
		hw->irq_callback(hw->irq_callback_data, status);

	hw_write_20kx(hw, GIP, status);
	return IRQ_HANDLED;
}