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
#define  RT5514_VENDOR_ID1 129 
#define  RT5514_VENDOR_ID2 128 

__attribute__((used)) static bool rt5514_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT5514_VENDOR_ID1:
	case RT5514_VENDOR_ID2:
		return true;

	default:
		return false;
	}
}