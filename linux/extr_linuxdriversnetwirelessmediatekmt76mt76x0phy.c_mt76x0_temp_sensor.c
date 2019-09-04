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
typedef  int u8 ;
typedef  int u32 ;
struct mt76x0_dev {TYPE_1__* ee; } ;
typedef  int s32 ;
struct TYPE_2__ {int temp_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_RF (int,int) ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int rf_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mt76x0_temp_sensor(struct mt76x0_dev *dev)
{
	u8 rf_b7_73, rf_b0_66, rf_b0_67;
	int cycle, temp;
	u32 val;
	s32 sval;

	rf_b7_73 = rf_rr(dev, MT_RF(7, 73));
	rf_b0_66 = rf_rr(dev, MT_RF(0, 66));
	rf_b0_67 = rf_rr(dev, MT_RF(0, 73));

	rf_wr(dev, MT_RF(7, 73), 0x02);
	rf_wr(dev, MT_RF(0, 66), 0x23);
	rf_wr(dev, MT_RF(0, 73), 0x01);

	mt76_wr(dev, MT_BBP(CORE, 34), 0x00080055);

	for (cycle = 0; cycle < 2000; cycle++) {
		val = mt76_rr(dev, MT_BBP(CORE, 34));
		if (!(val & 0x10))
			break;
		udelay(3);
	}

	if (cycle >= 2000) {
		val &= 0x10;
		mt76_wr(dev, MT_BBP(CORE, 34), val);
		goto done;
	}

	sval = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;
	if (!(sval & 0x80))
		sval &= 0x7f; /* Positive */
	else
		sval |= 0xffffff00; /* Negative */

	temp = (35 * (sval - dev->ee->temp_off))/ 10 + 25;

done:
	rf_wr(dev, MT_RF(7, 73), rf_b7_73);
	rf_wr(dev, MT_RF(0, 66), rf_b0_66);
	rf_wr(dev, MT_RF(0, 73), rf_b0_67);
}