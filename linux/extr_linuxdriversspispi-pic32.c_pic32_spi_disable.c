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
struct pic32_spi {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_clr; } ;

/* Variables and functions */
 int CTRL_ON ; 
 int CTRL_SIDL ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pic32_spi_disable(struct pic32_spi *pic32s)
{
	writel(CTRL_ON | CTRL_SIDL, &pic32s->regs->ctrl_clr);

	/* avoid SPI registers read/write at immediate next CPU clock */
	ndelay(20);
}