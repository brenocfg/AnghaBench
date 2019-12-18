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
struct davinci_mcasp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ACLKXDIV_MASK ; 
 int AHCLKXE ; 
 int /*<<< orphan*/  DAVINCI_MCASP_AHCLKXCTL_REG ; 
 int /*<<< orphan*/  MCASP_CLKDIV_AUXCLK ; 
 int /*<<< orphan*/  MCASP_CLKDIV_BCLK ; 
 int /*<<< orphan*/  __davinci_mcasp_set_clkdiv (struct davinci_mcasp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ div64_long (long long,int) ; 
 int mcasp_get_reg (struct davinci_mcasp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_mcasp_calc_clk_div(struct davinci_mcasp *mcasp,
				      unsigned int sysclk_freq,
				      unsigned int bclk_freq, bool set)
{
	u32 reg = mcasp_get_reg(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG);
	int div = sysclk_freq / bclk_freq;
	int rem = sysclk_freq % bclk_freq;
	int error_ppm;
	int aux_div = 1;

	if (div > (ACLKXDIV_MASK + 1)) {
		if (reg & AHCLKXE) {
			aux_div = div / (ACLKXDIV_MASK + 1);
			if (div % (ACLKXDIV_MASK + 1))
				aux_div++;

			sysclk_freq /= aux_div;
			div = sysclk_freq / bclk_freq;
			rem = sysclk_freq % bclk_freq;
		} else if (set) {
			dev_warn(mcasp->dev, "Too fast reference clock (%u)\n",
				 sysclk_freq);
		}
	}

	if (rem != 0) {
		if (div == 0 ||
		    ((sysclk_freq / div) - bclk_freq) >
		    (bclk_freq - (sysclk_freq / (div+1)))) {
			div++;
			rem = rem - bclk_freq;
		}
	}
	error_ppm = (div*1000000 + (int)div64_long(1000000LL*rem,
		     (int)bclk_freq)) / div - 1000000;

	if (set) {
		if (error_ppm)
			dev_info(mcasp->dev, "Sample-rate is off by %d PPM\n",
				 error_ppm);

		__davinci_mcasp_set_clkdiv(mcasp, MCASP_CLKDIV_BCLK, div, 0);
		if (reg & AHCLKXE)
			__davinci_mcasp_set_clkdiv(mcasp, MCASP_CLKDIV_AUXCLK,
						   aux_div, 0);
	}

	return error_ppm;
}