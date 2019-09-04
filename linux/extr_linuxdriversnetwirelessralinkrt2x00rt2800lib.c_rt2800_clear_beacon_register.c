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
struct rt2x00_dev {TYPE_1__* bcn; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int winfo_size; } ;

/* Variables and functions */
 unsigned int rt2800_hw_beacon_base (struct rt2x00_dev*,unsigned int) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rt2800_clear_beacon_register(struct rt2x00_dev *rt2x00dev,
						unsigned int index)
{
	int i;
	const int txwi_desc_size = rt2x00dev->bcn->winfo_size;
	unsigned int beacon_base;

	beacon_base = rt2800_hw_beacon_base(rt2x00dev, index);

	/*
	 * For the Beacon base registers we only need to clear
	 * the whole TXWI which (when set to 0) will invalidate
	 * the entire beacon.
	 */
	for (i = 0; i < txwi_desc_size; i += sizeof(__le32))
		rt2800_register_write(rt2x00dev, beacon_base + i, 0);
}