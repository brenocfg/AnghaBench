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
typedef  int u8 ;
struct ltc294x_info {scalar_t__ id; int r_sense; int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LTC2943_REG_CURRENT_MSB ; 
 scalar_t__ LTC2944_ID ; 
 int ltc294x_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ltc294x_get_current(const struct ltc294x_info *info, int *val)
{
	int ret;
	u8 datar[2];
	s32 value;

	ret = ltc294x_read_regs(info->client,
		LTC2943_REG_CURRENT_MSB, &datar[0], 2);
	value = (datar[0] << 8) | datar[1];
	value -= 0x7FFF;
	if (info->id == LTC2944_ID)
		value *= 64000;
	else
		value *= 60000;
	/* Value is in range -32k..+32k, r_sense is usually 10..50 mOhm,
	 * the formula below keeps everything in s32 range while preserving
	 * enough digits */
	*val = 1000 * (value / (info->r_sense * 0x7FFF)); /* in uA */
	return ret;
}