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
typedef  int u32 ;

/* Variables and functions */
 int HIF_8601_SILICON ; 
 int HIF_8601_VERSATILE ; 
 int HIF_9000_SILICON_VERSATILE ; 

__attribute__((used)) static int cw1200_get_hw_type(u32 config_reg_val, int *major_revision)
{
	int hw_type = -1;
	u32 silicon_type = (config_reg_val >> 24) & 0x7;
	u32 silicon_vers = (config_reg_val >> 31) & 0x1;

	switch (silicon_type) {
	case 0x00:
		*major_revision = 1;
		hw_type = HIF_9000_SILICON_VERSATILE;
		break;
	case 0x01:
	case 0x02: /* CW1x00 */
	case 0x04: /* CW1x60 */
		*major_revision = silicon_type;
		if (silicon_vers)
			hw_type = HIF_8601_VERSATILE;
		else
			hw_type = HIF_8601_SILICON;
		break;
	default:
		break;
	}

	return hw_type;
}