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
struct mt7620_gsw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7530_mdio_r32 (struct mt7620_gsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_mdio_w32 (struct mt7620_gsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt7530_mdio_m32(struct mt7620_gsw *gsw, u32 mask, u32 set, u32 reg)
{
	u32 val = mt7530_mdio_r32(gsw, reg);

	val &= ~mask;
	val |= set;
	mt7530_mdio_w32(gsw, reg, val);
}