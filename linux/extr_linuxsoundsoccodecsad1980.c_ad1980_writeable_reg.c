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
#define  AC97_VENDOR_ID1 129 
#define  AC97_VENDOR_ID2 128 
 int ad1980_readable_reg (struct device*,unsigned int) ; 

__attribute__((used)) static bool ad1980_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AC97_VENDOR_ID1:
	case AC97_VENDOR_ID2:
		return false;
	default:
		return ad1980_readable_reg(dev, reg);
	}
}