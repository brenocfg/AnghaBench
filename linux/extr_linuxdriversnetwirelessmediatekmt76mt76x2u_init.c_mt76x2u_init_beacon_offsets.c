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
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_BCN_OFFSET (int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x2u_init_beacon_offsets(struct mt76x2_dev *dev)
{
	mt76_wr(dev, MT_BCN_OFFSET(0), 0x18100800);
	mt76_wr(dev, MT_BCN_OFFSET(1), 0x38302820);
	mt76_wr(dev, MT_BCN_OFFSET(2), 0x58504840);
	mt76_wr(dev, MT_BCN_OFFSET(3), 0x78706860);
}