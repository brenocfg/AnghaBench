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
typedef  unsigned short u32 ;
struct snd_ac97 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA20_AC97_CMD ; 
 unsigned short TEGRA20_AC97_CMD_BUSY ; 
 unsigned short TEGRA20_AC97_CMD_CMD_ADDR_MASK ; 
 unsigned short TEGRA20_AC97_CMD_CMD_ADDR_SHIFT ; 
 unsigned short TEGRA20_AC97_CMD_CMD_DATA_MASK ; 
 unsigned short TEGRA20_AC97_CMD_CMD_DATA_SHIFT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 TYPE_1__* workdata ; 

__attribute__((used)) static void tegra20_ac97_codec_write(struct snd_ac97 *ac97_snd,
				     unsigned short reg, unsigned short val)
{
	u32 readback;
	unsigned long timeout;

	regmap_write(workdata->regmap, TEGRA20_AC97_CMD,
		     ((reg << TEGRA20_AC97_CMD_CMD_ADDR_SHIFT) &
		      TEGRA20_AC97_CMD_CMD_ADDR_MASK) |
		     ((val << TEGRA20_AC97_CMD_CMD_DATA_SHIFT) &
		      TEGRA20_AC97_CMD_CMD_DATA_MASK) |
		     TEGRA20_AC97_CMD_BUSY);

	timeout = jiffies + msecs_to_jiffies(100);

	do {
		regmap_read(workdata->regmap, TEGRA20_AC97_CMD, &readback);
		if (!(readback & TEGRA20_AC97_CMD_BUSY))
			break;
		usleep_range(1000, 2000);
	} while (!time_after(jiffies, timeout));
}