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
struct mt7620_gsw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GSW_MDIO_ACCESS ; 
 scalar_t__ GSW_REG_PHY_TIMEOUT ; 
 int /*<<< orphan*/  MT7620A_GSW_REG_PIAC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int mtk_switch_r32 (struct mt7620_gsw*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int mt7620_mii_busy_wait(struct mt7620_gsw *gsw)
{
	unsigned long t_start = jiffies;

	while (1) {
		if (!(mtk_switch_r32(gsw, MT7620A_GSW_REG_PIAC) & GSW_MDIO_ACCESS))
			return 0;
		if (time_after(jiffies, t_start + GSW_REG_PHY_TIMEOUT))
			break;
	}

	dev_err(gsw->dev, "mdio: MDIO timeout\n");
	return -1;
}