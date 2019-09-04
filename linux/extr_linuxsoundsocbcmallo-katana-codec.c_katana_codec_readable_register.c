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
#define  KATANA_CODEC_CHIP_ID_REG 128 

__attribute__((used)) static bool katana_codec_readable_register(struct device *dev,
				unsigned int reg)
{
	switch (reg) {
	case KATANA_CODEC_CHIP_ID_REG:
		return true;
	default:
		return reg < 0xff;
	}
}