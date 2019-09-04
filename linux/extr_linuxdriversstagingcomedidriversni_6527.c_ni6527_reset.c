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
 int NI6527_CLR_IRQS ; 
 scalar_t__ NI6527_CLR_REG ; 
 int NI6527_CLR_RESET_FILT ; 
 int NI6527_CTRL_DISABLE_IRQS ; 
 scalar_t__ NI6527_CTRL_REG ; 
 int /*<<< orphan*/  ni6527_set_edge_detection (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni6527_set_filter_enable (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ni6527_reset(struct comedi_device *dev)
{
	/* disable deglitch filters on all channels */
	ni6527_set_filter_enable(dev, 0);

	/* disable edge detection */
	ni6527_set_edge_detection(dev, 0xffffffff, 0, 0);

	writeb(NI6527_CLR_IRQS | NI6527_CLR_RESET_FILT,
	       dev->mmio + NI6527_CLR_REG);
	writeb(NI6527_CTRL_DISABLE_IRQS, dev->mmio + NI6527_CTRL_REG);
}