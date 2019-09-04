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
struct iss_device {int subclk_resources; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ISS_CLKCTRL ; 
 int ISS_CLKCTRL_CSI2_A ; 
 int ISS_CLKCTRL_CSI2_B ; 
 int ISS_CLKCTRL_ISP ; 
 int ISS_CLKCTRL_MASK ; 
 int /*<<< orphan*/  ISS_CLKSTAT ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_TOP ; 
 int OMAP4_ISS_SUBCLK_CSI2_A ; 
 int OMAP4_ISS_SUBCLK_CSI2_B ; 
 int OMAP4_ISS_SUBCLK_ISP ; 
 int iss_reg_read (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_update (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int __iss_subclk_update(struct iss_device *iss)
{
	u32 clk = 0;
	int ret = 0, timeout = 1000;

	if (iss->subclk_resources & OMAP4_ISS_SUBCLK_CSI2_A)
		clk |= ISS_CLKCTRL_CSI2_A;

	if (iss->subclk_resources & OMAP4_ISS_SUBCLK_CSI2_B)
		clk |= ISS_CLKCTRL_CSI2_B;

	if (iss->subclk_resources & OMAP4_ISS_SUBCLK_ISP)
		clk |= ISS_CLKCTRL_ISP;

	iss_reg_update(iss, OMAP4_ISS_MEM_TOP, ISS_CLKCTRL,
		       ISS_CLKCTRL_MASK, clk);

	/* Wait for HW assertion */
	while (--timeout > 0) {
		udelay(1);
		if ((iss_reg_read(iss, OMAP4_ISS_MEM_TOP, ISS_CLKSTAT) &
		    ISS_CLKCTRL_MASK) == clk)
			break;
	}

	if (!timeout)
		ret = -EBUSY;

	return ret;
}