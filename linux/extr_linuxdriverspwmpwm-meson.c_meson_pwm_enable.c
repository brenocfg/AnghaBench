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
struct meson_pwm_channel {int pre_div; int hi; int lo; } ;
struct meson_pwm {scalar_t__ base; } ;

/* Variables and functions */
 int MISC_A_CLK_DIV_SHIFT ; 
 int MISC_A_CLK_EN ; 
 int MISC_A_EN ; 
 int MISC_B_CLK_DIV_SHIFT ; 
 int MISC_B_CLK_EN ; 
 int MISC_B_EN ; 
 int MISC_CLK_DIV_MASK ; 
 int PWM_HIGH_SHIFT ; 
 scalar_t__ REG_MISC_AB ; 
 unsigned int REG_PWM_A ; 
 unsigned int REG_PWM_B ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_pwm_enable(struct meson_pwm *meson,
			     struct meson_pwm_channel *channel,
			     unsigned int id)
{
	u32 value, clk_shift, clk_enable, enable;
	unsigned int offset;

	switch (id) {
	case 0:
		clk_shift = MISC_A_CLK_DIV_SHIFT;
		clk_enable = MISC_A_CLK_EN;
		enable = MISC_A_EN;
		offset = REG_PWM_A;
		break;

	case 1:
		clk_shift = MISC_B_CLK_DIV_SHIFT;
		clk_enable = MISC_B_CLK_EN;
		enable = MISC_B_EN;
		offset = REG_PWM_B;
		break;

	default:
		return;
	}

	value = readl(meson->base + REG_MISC_AB);
	value &= ~(MISC_CLK_DIV_MASK << clk_shift);
	value |= channel->pre_div << clk_shift;
	value |= clk_enable;
	writel(value, meson->base + REG_MISC_AB);

	value = (channel->hi << PWM_HIGH_SHIFT) | channel->lo;
	writel(value, meson->base + offset);

	value = readl(meson->base + REG_MISC_AB);
	value |= enable;
	writel(value, meson->base + REG_MISC_AB);
}