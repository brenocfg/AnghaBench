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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MHZ (int) ; 
 scalar_t__ NETSEC_GMAC_GAR_REG_CR_100_150_MHZ ; 
 scalar_t__ NETSEC_GMAC_GAR_REG_CR_150_250_MHZ ; 
 scalar_t__ NETSEC_GMAC_GAR_REG_CR_250_300_MHZ ; 
 scalar_t__ NETSEC_GMAC_GAR_REG_CR_25_35_MHZ ; 
 scalar_t__ NETSEC_GMAC_GAR_REG_CR_35_60_MHZ ; 
 scalar_t__ NETSEC_GMAC_GAR_REG_CR_60_100_MHZ ; 

__attribute__((used)) static u32 netsec_clk_type(u32 freq)
{
	if (freq < MHZ(35))
		return NETSEC_GMAC_GAR_REG_CR_25_35_MHZ;
	if (freq < MHZ(60))
		return NETSEC_GMAC_GAR_REG_CR_35_60_MHZ;
	if (freq < MHZ(100))
		return NETSEC_GMAC_GAR_REG_CR_60_100_MHZ;
	if (freq < MHZ(150))
		return NETSEC_GMAC_GAR_REG_CR_100_150_MHZ;
	if (freq < MHZ(250))
		return NETSEC_GMAC_GAR_REG_CR_150_250_MHZ;

	return NETSEC_GMAC_GAR_REG_CR_250_300_MHZ;
}