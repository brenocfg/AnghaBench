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
struct meson_dwmac {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int ETHMAC_SPEED_100 ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson6_dwmac_fix_mac_speed(void *priv, unsigned int speed)
{
	struct meson_dwmac *dwmac = priv;
	unsigned int val;

	val = readl(dwmac->reg);

	switch (speed) {
	case SPEED_10:
		val &= ~ETHMAC_SPEED_100;
		break;
	case SPEED_100:
		val |= ETHMAC_SPEED_100;
		break;
	}

	writel(val, dwmac->reg);
}