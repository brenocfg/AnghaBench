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
struct reg_channel_bounds {int member_0; int member_1; scalar_t__ num; scalar_t__ start; } ;
struct mt7601u_dev {TYPE_1__* ee; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct reg_channel_bounds reg; } ;

/* Variables and functions */
 size_t MT_EE_COUNTRY_REGION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
mt7601u_set_country_reg(struct mt7601u_dev *dev, u8 *eeprom)
{
	/* Note: - region 31 is not valid for mt7601u (see rtmp_init.c)
	 *	 - comments in rtmp_def.h are incorrect (see rt_channel.c)
	 */
	static const struct reg_channel_bounds chan_bounds[] = {
		/* EEPROM country regions 0 - 7 */
		{  1, 11 },	{  1, 13 },	{ 10,  2 },	{ 10,  4 },
		{ 14,  1 },	{  1, 14 },	{  3,  7 },	{  5,  9 },
		/* EEPROM country regions 32 - 33 */
		{  1, 11 },	{  1, 14 }
	};
	u8 val = eeprom[MT_EE_COUNTRY_REGION];
	int idx = -1;

	if (val < 8)
		idx = val;
	if (val > 31 && val < 33)
		idx = val - 32 + 8;

	if (idx != -1)
		dev_info(dev->dev,
			 "EEPROM country region %02hhx (channels %hhd-%hhd)\n",
			 val, chan_bounds[idx].start,
			 chan_bounds[idx].start + chan_bounds[idx].num - 1);
	else
		idx = 5; /* channels 1 - 14 */

	dev->ee->reg = chan_bounds[idx];

	/* TODO: country region 33 is special - phy should be set to B-mode
	 *	 before entering channel 14 (see sta/connect.c)
	 */
}