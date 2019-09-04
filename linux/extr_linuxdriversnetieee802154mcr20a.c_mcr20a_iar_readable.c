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
#define  IAR_DUAL_PAN_STS 133 
#define  IAR_FILTERFAIL_CODE1 132 
#define  IAR_FILTERFAIL_CODE2 131 
#define  IAR_PART_ID 130 
#define  IAR_RSSI 129 
#define  IAR_RX_BYTE_COUNT 128 
 int mcr20a_iar_writeable (struct device*,unsigned int) ; 

__attribute__((used)) static bool
mcr20a_iar_readable(struct device *dev, unsigned int reg)
{
	bool rc;

	/* all writeable are also readable */
	rc = mcr20a_iar_writeable(dev, reg);
	if (rc)
		return rc;

	/* readonly regs */
	switch (reg) {
	case IAR_PART_ID:
	case IAR_DUAL_PAN_STS:
	case IAR_RX_BYTE_COUNT:
	case IAR_FILTERFAIL_CODE1:
	case IAR_FILTERFAIL_CODE2:
	case IAR_RSSI:
		return true;
	default:
		return false;
	}
}