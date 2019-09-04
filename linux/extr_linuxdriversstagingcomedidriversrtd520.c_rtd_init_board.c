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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ LAS0_ADC_FIFO_CLEAR ; 
 scalar_t__ LAS0_CGT_CLEAR ; 
 scalar_t__ LAS0_DAC_RESET (int) ; 
 scalar_t__ LAS0_DIO_STATUS ; 
 scalar_t__ LAS0_OVERRUN ; 
 int /*<<< orphan*/  rtd_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtd_init_board(struct comedi_device *dev)
{
	rtd_reset(dev);

	writel(0, dev->mmio + LAS0_OVERRUN);
	writel(0, dev->mmio + LAS0_CGT_CLEAR);
	writel(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	writel(0, dev->mmio + LAS0_DAC_RESET(0));
	writel(0, dev->mmio + LAS0_DAC_RESET(1));
	/* clear digital IO fifo */
	writew(0, dev->mmio + LAS0_DIO_STATUS);
	/* TODO: set user out source ??? */
}