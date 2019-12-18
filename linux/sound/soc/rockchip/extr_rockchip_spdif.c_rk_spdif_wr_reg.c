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
#define  SPDIF_CFGR 132 
#define  SPDIF_DMACR 131 
#define  SPDIF_INTCR 130 
#define  SPDIF_SMPDR 129 
#define  SPDIF_XFER 128 

__attribute__((used)) static bool rk_spdif_wr_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SPDIF_CFGR:
	case SPDIF_DMACR:
	case SPDIF_INTCR:
	case SPDIF_XFER:
	case SPDIF_SMPDR:
		return true;
	default:
		return false;
	}
}