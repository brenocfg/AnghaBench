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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  VX855_GPI (int) ; 
 int /*<<< orphan*/  dcon_clear_irq () ; 
 int /*<<< orphan*/  dcon_was_irq () ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcon_read_status_xo_1_5(u8 *status)
{
	if (!dcon_was_irq())
		return -1;

	/* i believe this is the same as "inb(0x44b) & 3" */
	*status = gpio_get_value(VX855_GPI(10));
	*status |= gpio_get_value(VX855_GPI(11)) << 1;

	dcon_clear_irq();

	return 0;
}