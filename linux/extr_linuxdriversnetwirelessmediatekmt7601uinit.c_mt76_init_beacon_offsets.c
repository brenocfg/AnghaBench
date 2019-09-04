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
struct mt7601u_dev {int* beacon_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_BCN_OFFSET (int) ; 
 int MT_BEACON_BASE ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76_init_beacon_offsets(struct mt7601u_dev *dev)
{
	u16 base = MT_BEACON_BASE;
	u32 regs[4] = {};
	int i;

	for (i = 0; i < 16; i++) {
		u16 addr = dev->beacon_offsets[i];

		regs[i / 4] |= ((addr - base) / 64) << (8 * (i % 4));
	}

	for (i = 0; i < 4; i++)
		mt7601u_wr(dev, MT_BCN_OFFSET(i), regs[i]);
}