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
struct radeonfb_info {int dummy; } ;
struct radeon_i2c_chan {int /*<<< orphan*/  ddc_reg; struct radeonfb_info* rinfo; } ;

/* Variables and functions */
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int VGA_DDC_DATA_OUT_EN ; 

__attribute__((used)) static void radeon_gpio_setsda(void* data, int state)
{
	struct radeon_i2c_chan 	*chan = data;
	struct radeonfb_info	*rinfo = chan->rinfo;
	u32			val;
	
	val = INREG(chan->ddc_reg) & ~(VGA_DDC_DATA_OUT_EN);
	if (!state)
		val |= VGA_DDC_DATA_OUT_EN;

	OUTREG(chan->ddc_reg, val);
	(void)INREG(chan->ddc_reg);
}