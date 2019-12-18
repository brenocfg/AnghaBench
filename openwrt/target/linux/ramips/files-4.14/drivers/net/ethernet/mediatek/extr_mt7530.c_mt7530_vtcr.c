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
struct mt7530_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_ESW_VLAN_VTCR ; 
 int mt7530_r32 (struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_w32 (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mt7530_vtcr(struct mt7530_priv *priv, u32 cmd, u32 val)
{
	int i;

	mt7530_w32(priv, REG_ESW_VLAN_VTCR, BIT(31) | (cmd << 12) | val);

	for (i = 0; i < 20; i++) {
		u32 val = mt7530_r32(priv, REG_ESW_VLAN_VTCR);

		if ((val & BIT(31)) == 0)
			break;

		udelay(1000);
	}
	if (i == 20)
		printk("mt7530: vtcr timeout\n");
}