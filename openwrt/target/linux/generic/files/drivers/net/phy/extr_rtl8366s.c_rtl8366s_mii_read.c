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
struct rtl8366_smi {int dummy; } ;
struct mii_bus {struct rtl8366_smi* priv; } ;

/* Variables and functions */
 int rtl8366s_read_phy_reg (struct rtl8366_smi*,int,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int rtl8366s_mii_read(struct mii_bus *bus, int addr, int reg)
{
	struct rtl8366_smi *smi = bus->priv;
	u32 val = 0;
	int err;

	err = rtl8366s_read_phy_reg(smi, addr, 0, reg, &val);
	if (err)
		return 0xffff;

	return val;
}