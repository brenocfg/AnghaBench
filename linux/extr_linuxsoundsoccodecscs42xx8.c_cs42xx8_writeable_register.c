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
#define  CS42XX8_CHIPID 129 
#define  CS42XX8_STATUS 128 

__attribute__((used)) static bool cs42xx8_writeable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS42XX8_CHIPID:
	case CS42XX8_STATUS:
		return false;
	default:
		return true;
	}
}