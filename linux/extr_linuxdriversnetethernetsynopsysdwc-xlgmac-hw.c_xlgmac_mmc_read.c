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
typedef  int u64 ;
struct xlgmac_pdata {scalar_t__ mac_regs; } ;

/* Variables and functions */
#define  MMC_RXOCTETCOUNT_GB_LO 131 
#define  MMC_RXOCTETCOUNT_G_LO 130 
#define  MMC_TXOCTETCOUNT_GB_LO 129 
#define  MMC_TXOCTETCOUNT_G_LO 128 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u64 xlgmac_mmc_read(struct xlgmac_pdata *pdata, unsigned int reg_lo)
{
	bool read_hi;
	u64 val;

	switch (reg_lo) {
	/* These registers are always 64 bit */
	case MMC_TXOCTETCOUNT_GB_LO:
	case MMC_TXOCTETCOUNT_G_LO:
	case MMC_RXOCTETCOUNT_GB_LO:
	case MMC_RXOCTETCOUNT_G_LO:
		read_hi = true;
		break;

	default:
		read_hi = false;
	}

	val = (u64)readl(pdata->mac_regs + reg_lo);

	if (read_hi)
		val |= ((u64)readl(pdata->mac_regs + reg_lo + 4) << 32);

	return val;
}