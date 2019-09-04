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
typedef  int /*<<< orphan*/  u8 ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL_ADDR ; 
 int /*<<< orphan*/  CLOCK_CNTL_DATA ; 
 int PLL_ADDR ; 
 int /*<<< orphan*/  aty_ld_8 (int /*<<< orphan*/ ,struct atyfb_par const*) ; 
 int /*<<< orphan*/  aty_st_8 (int /*<<< orphan*/ ,int,struct atyfb_par const*) ; 

u8 aty_ld_pll_ct(int offset, const struct atyfb_par *par)
{
	u8 res;

	/* write addr byte */
	aty_st_8(CLOCK_CNTL_ADDR, (offset << 2) & PLL_ADDR, par);
	/* read the register value */
	res = aty_ld_8(CLOCK_CNTL_DATA, par);
	return res;
}