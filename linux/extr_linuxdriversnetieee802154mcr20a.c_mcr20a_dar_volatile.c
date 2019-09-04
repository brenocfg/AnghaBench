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
#define  DAR_IRQ_STS1 130 
#define  DAR_IRQ_STS2 129 
#define  DAR_IRQ_STS3 128 

__attribute__((used)) static bool
mcr20a_dar_volatile(struct device *dev, unsigned int reg)
{
	/* can be changed during runtime */
	switch (reg) {
	case DAR_IRQ_STS1:
	case DAR_IRQ_STS2:
	case DAR_IRQ_STS3:
	/* use them in spi_async and regmap so it's volatile */
		return true;
	default:
		return false;
	}
}