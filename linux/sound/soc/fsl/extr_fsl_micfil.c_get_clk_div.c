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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_micfil {int /*<<< orphan*/  mclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MICFIL_CTRL2 ; 
 long clk_get_rate (int /*<<< orphan*/ ) ; 
 int get_pdm_clk (struct fsl_micfil*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_clk_div(struct fsl_micfil *micfil,
			      unsigned int rate)
{
	u32 ctrl2_reg;
	long mclk_rate;
	int clk_div;

	regmap_read(micfil->regmap, REG_MICFIL_CTRL2, &ctrl2_reg);

	mclk_rate = clk_get_rate(micfil->mclk);

	clk_div = mclk_rate / (get_pdm_clk(micfil, rate) * 2);

	return clk_div;
}