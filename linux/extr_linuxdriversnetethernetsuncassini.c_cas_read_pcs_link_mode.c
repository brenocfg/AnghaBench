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
struct cas {scalar_t__ regs; } ;

/* Variables and functions */
 int PCS_MII_LPA_ASYM_PAUSE ; 
 int PCS_MII_LPA_FD ; 
 int PCS_MII_LPA_SYM_PAUSE ; 
 scalar_t__ REG_PCS_MII_LPA ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void cas_read_pcs_link_mode(struct cas *cp, int *fd, int *spd,
				   int *pause)
{
	u32 val = readl(cp->regs + REG_PCS_MII_LPA);
	*fd     = (val & PCS_MII_LPA_FD) ? 1 : 0;
	*pause  = (val & PCS_MII_LPA_SYM_PAUSE) ? 0x01 : 0x00;
	if (val & PCS_MII_LPA_ASYM_PAUSE)
		*pause |= 0x10;
	*spd = 1000;
}