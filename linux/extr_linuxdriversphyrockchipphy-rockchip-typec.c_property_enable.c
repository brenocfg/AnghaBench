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
struct usb3phy_reg {int write_enable; int enable_bit; int /*<<< orphan*/  offset; } ;
struct rockchip_typec_phy {int /*<<< orphan*/  grf_regs; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int property_enable(struct rockchip_typec_phy *tcphy,
				  const struct usb3phy_reg *reg, bool en)
{
	u32 mask = 1 << reg->write_enable;
	u32 val = en << reg->enable_bit;

	return regmap_write(tcphy->grf_regs, reg->offset, val | mask);
}