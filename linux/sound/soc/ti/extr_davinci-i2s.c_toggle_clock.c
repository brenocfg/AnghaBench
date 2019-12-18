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
struct davinci_mcbsp_dev {int pcr; } ;

/* Variables and functions */
 int DAVINCI_MCBSP_PCR_CLKRP ; 
 int DAVINCI_MCBSP_PCR_CLKXP ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_PCR_REG ; 
 int /*<<< orphan*/  davinci_mcbsp_write_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void toggle_clock(struct davinci_mcbsp_dev *dev, int playback)
{
	u32 m = playback ? DAVINCI_MCBSP_PCR_CLKXP : DAVINCI_MCBSP_PCR_CLKRP;
	/* The clock needs to toggle to complete reset.
	 * So, fake it by toggling the clk polarity.
	 */
	davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_PCR_REG, dev->pcr ^ m);
	davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_PCR_REG, dev->pcr);
}