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
struct meson_pwm {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_A_EN ; 
 int /*<<< orphan*/  MISC_B_EN ; 
 scalar_t__ REG_MISC_AB ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_pwm_disable(struct meson_pwm *meson, unsigned int id)
{
	u32 value, enable;

	switch (id) {
	case 0:
		enable = MISC_A_EN;
		break;

	case 1:
		enable = MISC_B_EN;
		break;

	default:
		return;
	}

	value = readl(meson->base + REG_MISC_AB);
	value &= ~enable;
	writel(value, meson->base + REG_MISC_AB);
}