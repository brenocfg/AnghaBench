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
#define  LTC3676_IRQSTAT 130 
#define  LTC3676_PGSTATL 129 
#define  LTC3676_PGSTATRT 128 

__attribute__((used)) static bool ltc3676_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LTC3676_IRQSTAT:
	case LTC3676_PGSTATL:
	case LTC3676_PGSTATRT:
		return true;
	}
	return false;
}