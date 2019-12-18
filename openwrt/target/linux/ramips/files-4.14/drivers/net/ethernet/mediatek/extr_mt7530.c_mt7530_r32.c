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
typedef  int u16 ;
struct mt7530_priv {scalar_t__ base; scalar_t__ bus; } ;

/* Variables and functions */
 int ioread32 (scalar_t__) ; 
 int mdiobus_read (scalar_t__,int,int) ; 
 int /*<<< orphan*/  mdiobus_write (scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static u32
mt7530_r32(struct mt7530_priv *priv, u32 reg)
{
	u32 val;
	if (priv->bus) {
		u16 high, low;

		mdiobus_write(priv->bus, 0x1f, 0x1f, (reg >> 6) & 0x3ff);
		low = mdiobus_read(priv->bus, 0x1f, (reg >> 2) & 0xf);
		high = mdiobus_read(priv->bus, 0x1f, 0x10);

		return (high << 16) | (low & 0xffff);
	}

	val = ioread32(priv->base + reg);
	pr_debug("MT7530 MDIO Read [%04x]=%08x\n", reg, val);

	return val;
}