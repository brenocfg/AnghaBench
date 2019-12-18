#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mii_bus {struct ar8xxx_priv* priv; } ;
struct ar8xxx_priv {TYPE_1__* chip; } ;
struct TYPE_2__ {int (* phy_read ) (struct ar8xxx_priv*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct ar8xxx_priv*,int,int) ; 

__attribute__((used)) static int
ar8xxx_phy_read(struct mii_bus *bus, int phy_addr, int reg_addr)
{
	struct ar8xxx_priv *priv = bus->priv;
	return priv->chip->phy_read(priv, phy_addr, reg_addr);
}