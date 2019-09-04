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
struct rtd_private {scalar_t__ ai_count; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ mmio; struct rtd_private* private; } ;

/* Variables and functions */
 scalar_t__ LAS0_ADC_CONVERSION ; 
 scalar_t__ LAS0_ADC_FIFO_CLEAR ; 
 scalar_t__ LAS0_IT ; 
 scalar_t__ LAS0_PACER ; 
 scalar_t__ LAS0_PACER_STOP ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtd_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct rtd_private *devpriv = dev->private;

	/* pacer stop source: SOFTWARE */
	writel(0, dev->mmio + LAS0_PACER_STOP);
	writel(0, dev->mmio + LAS0_PACER);	/* stop pacer */
	writel(0, dev->mmio + LAS0_ADC_CONVERSION);
	writew(0, dev->mmio + LAS0_IT);
	devpriv->ai_count = 0;	/* stop and don't transfer any more */
	writel(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	return 0;
}