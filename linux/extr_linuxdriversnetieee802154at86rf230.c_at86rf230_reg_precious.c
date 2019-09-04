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
struct device {int dummy; } ;

/* Variables and functions */
#define  RG_IRQ_STATUS 128 

__attribute__((used)) static bool
at86rf230_reg_precious(struct device *dev, unsigned int reg)
{
	/* don't clear irq line on read */
	switch (reg) {
	case RG_IRQ_STATUS:
		return true;
	default:
		return false;
	}
}