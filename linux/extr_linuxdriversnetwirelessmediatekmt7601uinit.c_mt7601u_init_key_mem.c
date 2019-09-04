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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MT_SKEY_MODE_BASE_0 ; 
 int mt7601u_burst_write_regs (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_init_key_mem(struct mt7601u_dev *dev)
{
	u32 vals[4] = {};

	return mt7601u_burst_write_regs(dev, MT_SKEY_MODE_BASE_0,
					vals, ARRAY_SIZE(vals));
}