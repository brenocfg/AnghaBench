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
struct rt1305_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int R0_LOWER ; 
 int R0_UPPER ; 
 scalar_t__ RT1305_ADC_SET_3 ; 
 scalar_t__ RT1305_CAL_EFUSE_CLOCK ; 
 scalar_t__ RT1305_CLK_1 ; 
 scalar_t__ RT1305_CLOCK_DETECT ; 
 scalar_t__ RT1305_DAC_OFFSET_5 ; 
 scalar_t__ RT1305_DAC_OFFSET_6 ; 
 scalar_t__ RT1305_DAC_OFFSET_7 ; 
 scalar_t__ RT1305_DAC_OFFSET_8 ; 
 scalar_t__ RT1305_EFUSE_1 ; 
 scalar_t__ RT1305_POWER_CTRL_1 ; 
 scalar_t__ RT1305_POWER_CTRL_2 ; 
 scalar_t__ RT1305_POWER_CTRL_3 ; 
 scalar_t__ RT1305_POWER_STATUS ; 
 scalar_t__ RT1305_PR_BASE ; 
 scalar_t__ RT1305_SILENCE_DETECT ; 
 scalar_t__ RT1305_SPK_TEMP_PROTECTION_1 ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rt1305_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt1305_calibrate(struct rt1305_priv *rt1305)
{
	unsigned int valmsb, vallsb, offsetl, offsetr;
	unsigned int rh, rl, rhl, r0ohm;
	u64 r0l, r0r;

	regcache_cache_bypass(rt1305->regmap, true);

	rt1305_reset(rt1305->regmap);
	regmap_write(rt1305->regmap, RT1305_ADC_SET_3, 0x0219);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xcf, 0x5548);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xc1, 0x0320);
	regmap_write(rt1305->regmap, RT1305_CLOCK_DETECT, 0x1000);
	regmap_write(rt1305->regmap, RT1305_CLK_1, 0x0600);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xffd0);
	regmap_write(rt1305->regmap, RT1305_EFUSE_1, 0x0080);
	regmap_write(rt1305->regmap, RT1305_EFUSE_1, 0x0880);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_1, 0x0dfe);

	/* Sin Gen */
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x5d, 0x0442);

	regmap_write(rt1305->regmap, RT1305_CAL_EFUSE_CLOCK, 0xb000);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xc3, 0xd4a0);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xcc, 0x00cc);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xc1, 0x0320);
	regmap_write(rt1305->regmap, RT1305_POWER_STATUS, 0x0000);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_2, 0xffff);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfc20);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x06, 0x00c0);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfca0);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfce0);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfcf0);

	/* EFUSE read */
	regmap_write(rt1305->regmap, RT1305_EFUSE_1, 0x0080);
	regmap_write(rt1305->regmap, RT1305_EFUSE_1, 0x0880);
	regmap_write(rt1305->regmap, RT1305_EFUSE_1, 0x0880);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfce0);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfca0);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfc20);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x06, 0x0000);
	regmap_write(rt1305->regmap, RT1305_EFUSE_1, 0x0000);

	regmap_read(rt1305->regmap, RT1305_DAC_OFFSET_5, &valmsb);
	regmap_read(rt1305->regmap, RT1305_DAC_OFFSET_6, &vallsb);
	offsetl = valmsb << 16 | vallsb;
	regmap_read(rt1305->regmap, RT1305_DAC_OFFSET_7, &valmsb);
	regmap_read(rt1305->regmap, RT1305_DAC_OFFSET_8, &vallsb);
	offsetr = valmsb << 16 | vallsb;
	pr_info("DC offsetl=0x%x, offsetr=0x%x\n", offsetl, offsetr);

	/* R0 calibration */
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x5d, 0x9542);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfcf0);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_2, 0xffff);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_1, 0x1dfe);
	regmap_write(rt1305->regmap, RT1305_SILENCE_DETECT, 0x0e13);
	regmap_write(rt1305->regmap, RT1305_CLK_1, 0x0650);

	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x50, 0x0064);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x51, 0x0770);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x52, 0xc30c);
	regmap_write(rt1305->regmap, RT1305_SPK_TEMP_PROTECTION_1, 0x8200);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xfb00);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xff80);
	msleep(2000);
	regmap_read(rt1305->regmap, RT1305_PR_BASE + 0x55, &rh);
	regmap_read(rt1305->regmap, RT1305_PR_BASE + 0x56, &rl);
	rhl = (rh << 16) | rl;
	r0ohm = (rhl*10) / 33554432;

	pr_debug("Left_rhl = 0x%x rh=0x%x rl=0x%x\n", rhl, rh, rl);
	pr_info("Left channel %d.%dohm\n", (r0ohm/10), (r0ohm%10));

	r0l = 562949953421312ULL;
	if (rhl != 0)
		do_div(r0l, rhl);
	pr_debug("Left_r0 = 0x%llx\n", r0l);

	regmap_write(rt1305->regmap, RT1305_SPK_TEMP_PROTECTION_1, 0x9200);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xfb00);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xff80);
	msleep(2000);
	regmap_read(rt1305->regmap, RT1305_PR_BASE + 0x55, &rh);
	regmap_read(rt1305->regmap, RT1305_PR_BASE + 0x56, &rl);
	rhl = (rh << 16) | rl;
	r0ohm = (rhl*10) / 33554432;

	pr_debug("Right_rhl = 0x%x rh=0x%x rl=0x%x\n", rhl, rh, rl);
	pr_info("Right channel %d.%dohm\n", (r0ohm/10), (r0ohm%10));

	r0r = 562949953421312ULL;
	if (rhl != 0)
		do_div(r0r, rhl);
	pr_debug("Right_r0 = 0x%llx\n", r0r);

	regmap_write(rt1305->regmap, RT1305_SPK_TEMP_PROTECTION_1, 0xc2ec);

	if ((r0l > R0_UPPER) && (r0l < R0_LOWER) &&
		(r0r > R0_UPPER) && (r0r < R0_LOWER)) {
		regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x4e,
			(r0l >> 16) & 0xffff);
		regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x4f,
			r0l & 0xffff);
		regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xfe,
			((r0r >> 16) & 0xffff) | 0xf800);
		regmap_write(rt1305->regmap, RT1305_PR_BASE + 0xfd,
			r0r & 0xffff);
	} else {
		pr_err("R0 calibration failed\n");
	}

	/* restore some registers */
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_1, 0x0dfe);
	usleep_range(200000, 400000);
	regmap_write(rt1305->regmap, RT1305_PR_BASE + 0x5d, 0x0442);
	regmap_write(rt1305->regmap, RT1305_CLOCK_DETECT, 0x3000);
	regmap_write(rt1305->regmap, RT1305_CLK_1, 0x0400);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_1, 0x0000);
	regmap_write(rt1305->regmap, RT1305_CAL_EFUSE_CLOCK, 0x8000);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_2, 0x1020);
	regmap_write(rt1305->regmap, RT1305_POWER_CTRL_3, 0x0000);

	regcache_cache_bypass(rt1305->regmap, false);
}