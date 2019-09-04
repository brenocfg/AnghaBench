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
struct au1550_spi {int /*<<< orphan*/  (* irq_callback ) (struct au1550_spi*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct au1550_spi*) ; 

__attribute__((used)) static irqreturn_t au1550_spi_irq(int irq, void *dev)
{
	struct au1550_spi *hw = dev;
	return hw->irq_callback(hw);
}