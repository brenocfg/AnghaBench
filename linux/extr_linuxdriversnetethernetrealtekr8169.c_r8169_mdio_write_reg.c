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
typedef  int /*<<< orphan*/  u16 ;
struct rtl8169_private {int dummy; } ;
struct mii_bus {struct rtl8169_private* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r8169_mdio_write_reg(struct mii_bus *mii_bus, int phyaddr,
				int phyreg, u16 val)
{
	struct rtl8169_private *tp = mii_bus->priv;

	if (phyaddr > 0)
		return -ENODEV;

	rtl_writephy(tp, phyreg, val);

	return 0;
}